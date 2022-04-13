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
#include"hvector.h"

using namespace std;

hw5::HexVector::HexVector():AbstractHex()
    {}
hw5::HexVector::HexVector(const HEXCELL& player, const GAMETYPE& gameType, int size):AbstractHex(player,gameType){
    setSize(size);
}
const hw5::Cell& hw5::HexVector::operator()(int row, int column) const{
    try{
        checkIndex(row,column);
        return hexCells[row][column];
    }
    catch(invalidIndex& exc){
        cout << exc.what() << endl;
    }
}
hw5::Cell& hw5::HexVector::operator()(int row, int column){
    try{
        checkIndex(row,column);
        return hexCells[row][column];
    }
    catch(invalidIndex& exc){
        cout << exc.what() << endl;
    }
}
void hw5::HexVector::displayBoard(const vector<vector<Cell> > &board){
    cout << "\n\t\t";
    for(char c='a'; c-'a'<getBoardSize(); c++) cout << ' ' << c ;
    cout << endl;
    
    for(int i=0; i< getBoardSize(); ++i){
        cout << "\t\t";
        if(i < 9) 
            for(int k=0; k < i; k++) cout << ' ';      
        else 
            for(int k=0; k < i-1; k++) cout << ' ';
            
        cout << i+1 << ' ';
        for(int j=0; j<getBoardSize() ; ++j){
            cout << static_cast<char> (board[i][j].getPlayer());
            cout << ' ';
        }
        cout << endl;
    }
}

void hw5::HexVector::setSize(int size){
    if(size > 5){
        boardSize = size;
        hexCells.resize(boardSize);
        for(int i=0; i< boardSize ; i++)
            hexCells[i].resize(boardSize);
        reset();
        ifSizeSet = true;
    }
    else{
        cerr << "invalid size!\n"; 
    }
}

bool hw5::HexVector::isEnd(){
    
    vector<vector<Cell> > tempBoard;
    tempBoard = hexCells;
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
    return winFlag;
}
bool hw5::HexVector::isEndHelper(vector<vector<Cell> > &tempBoard,int row, int column){
    if(row >= 0 && row < getBoardSize() && column >= 0 && column < getBoardSize()){ // check it is in grid or not
        
        if(tempBoard[row][column].getPlayer() == otherUser){
            if(otherUser == userX) tempBoard[row][column].setCell(row,column,goneX);
            if(otherUser == userO) tempBoard[row][column].setCell(row,column,goneO);
            if(otherUser == userX && column == getBoardSize() -1) 
                return true;
            if(otherUser == userO && row == getBoardSize() -1)
                return true;
            else 
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