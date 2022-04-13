#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<random>
#include<algorithm>
#include<cstdlib>
#include<array>
#include<deque>
#include"cell.h"
#include"abstract.h"
#include"exceptions.h"
#include"array1d.h"
using namespace std;
hw5::HexArray1D::HexArray1D():hw5::AbstractHex(){
    hexCells = NULL;
}
hw5::HexArray1D::HexArray1D(const HEXCELL& player, const GAMETYPE& gameType, int size):hw5::AbstractHex(player,gameType){
    hexCells = NULL;
    setSize(size);
}
hw5::HexArray1D::~HexArray1D(){
    if(hexCells!=NULL) free(hexCells);
    hexCells = NULL;
}

hw5::HexArray1D::HexArray1D(const HexArray1D& other){
    if(hexCells != NULL) free(hexCells);
    this->setSize(other.getBoardSize());
    this->setGameType(other.gameType);
    this->setUser(other.playingUser);
    for(int i=0; i<getBoardSize();++i){
        for(int j=0; j<getBoardSize(); ++j){
            this->hexCells[i*getBoardSize()+j] = other.hexCells[i*getBoardSize()+j];
        }
    }
}
const hw5::HexArray1D& hw5::HexArray1D::operator=(const HexArray1D& other){
    if(this == &other)
        return *this;
    if(hexCells != NULL) free(hexCells);
    this->setSize(other.getBoardSize());
    this->setGameType(other.gameType);
    this->setUser(other.playingUser);
    for(int i=0; i<getBoardSize();++i){
        for(int j=0; j<getBoardSize(); ++j){
            this->hexCells[i*getBoardSize()+j] = other.hexCells[i*getBoardSize()+j];
        }
    }
    return *this;
}
const hw5::Cell& hw5::HexArray1D::operator()(int row,int column)const{
    try{
        checkIndex(row,column);
        return hexCells[row*getBoardSize() + column];
    }
    catch(const invalidIndex& e){
        cerr << e.what() << '\n';
    }
}
hw5::Cell& hw5::HexArray1D::operator()(int row,int column){
    try{
        checkIndex(row,column);
        return hexCells[row*getBoardSize() + column];
    }
    catch(const invalidIndex& e){
        cerr << e.what() << '\n';
    }
}


void hw5::HexArray1D::displayBoard(const Cell *board){
    cout << "\n\t\t";
    for(char c='a'; c-'a'<getBoardSize(); c++) cout << ' ' << c ;
    cout << endl;
    
    for(int i=0; i< getBoardSize(); i++){
        cout << "\t\t";
        if(i < 9) 
            for(int k=0; k < i; k++) cout << ' ';      
        else 
            for(int k=0; k < i-1; k++) cout << ' ';
            
        cout << i+1 << ' ';
        for(int j=0; j<getBoardSize() ; j++){
            cout << static_cast<char>(board[i*getBoardSize()+j].getPlayer());
            cout << ' ';
        }
        cout << endl;
    }
}

void hw5::HexArray1D::setSize(int size){
    if(size > 5){
        boardSize = size;
        if(hexCells != NULL){
            free(hexCells);
            hexCells = NULL;
        }
        hexCells = (Cell*)calloc(boardSize*boardSize,sizeof(Cell));
        reset();
        ifSizeSet = true;
    }
    else{
        cerr << "invalid size!\n"; 
    }
}


bool hw5::HexArray1D::isEnd(){
    Cell *tempBoard = (Cell*)calloc(getBoardSize()*getBoardSize(),sizeof(Cell));
    for(int i=0 ; i<getBoardSize()*getBoardSize();++i) tempBoard[i] = hexCells[i];
    bool winFlag = false;
    if(otherUser == userX){
        for(int i=0 ;i<getBoardSize() ;i++) winFlag = winFlag || isEndHelper(tempBoard,0+i,0);
    }
    if(otherUser == userO){
        for(int i=0 ;i<getBoardSize() ;i++) winFlag = winFlag || isEndHelper(tempBoard,0,0+i);
    }
    if(winFlag){
        displayBoard(tempBoard);
        cout << "\n\t\tGame Over!\n" << "User " << static_cast<char>(otherUser) << " WON!!\n";
    }
    free(tempBoard);
    tempBoard = NULL;
    return winFlag;
}
bool hw5::HexArray1D::isEndHelper(Cell *tempBoard,int row, int column){
    if(row >= 0 && row < getBoardSize() && column >= 0 && column < getBoardSize()){ // check it is in grid or not
        
        if(tempBoard[row*getBoardSize()+column].getPlayer() == otherUser){
            if(otherUser == userX){
                tempBoard[row*getBoardSize()+column].setCell(row,column,goneX);
            }
            if(otherUser == userO){
                tempBoard[row*getBoardSize()+column].setCell(row,column,goneO);
            }
            if(otherUser == userX && column == getBoardSize() -1) 
                return true;
            if(otherUser == userO && row == getBoardSize() -1)
                return true;

            return isEndHelper(tempBoard,row-1,column+1) || isEndHelper(tempBoard,row,column+1) || isEndHelper(tempBoard,row+1,column) || isEndHelper(tempBoard,row-1,column)||isEndHelper(tempBoard,row+1,column-1)|| isEndHelper(tempBoard,row,column-1);
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }  
}