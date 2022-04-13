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
#include"adapter.h"
using namespace std;


template <template <typename K,class Alloc = allocator<K>> class T>
hw5::HexAdapter<T>::HexAdapter() : hw5::AbstractHex()
    {}
template <template <typename K,class Alloc = allocator<K>> class T>
hw5::HexAdapter<T>::HexAdapter(const HEXCELL& player, const GAMETYPE& gameType, int size) : hw5::AbstractHex(player,gameType){
    setSize(size);
}
    
template <template <typename K,class Alloc = allocator<K>> class T>
const hw5::Cell& hw5::HexAdapter<T>::operator()(int row,int column) const{
    try{
        checkIndex(row,column);
        return hexCells[row][column];
    }
    catch(const hw5::invalidIndex& e){
        cerr << e.what() << '\n';
    }
}
template <template <typename K,class Alloc = allocator<K>> class T>
hw5::Cell& hw5::HexAdapter<T>::operator()(int row,int column){
    try{
        checkIndex(row,column);
        return hexCells[row][column];
    }
    catch(const hw5::invalidIndex& e){
        cerr << e.what() << '\n';
    }
}

template <template <typename K,class Alloc = allocator<K>> class T>
void hw5::HexAdapter<T>::displayBoard(const T<T<Cell> > &temp){
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
            cout << static_cast<char>(temp[i][j].getPlayer());
            cout << ' ';
        }
        cout << endl;
    }
}


template <template <typename K,class Alloc = allocator<K>> class T>
void hw5::HexAdapter<T>::setSize(int size){
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

template <template <typename K,class Alloc = allocator<K>> class T>
bool hw5::HexAdapter<T>::isEnd(){
    T<T<Cell> > tempBoard;
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
template <template <typename K,class Alloc = allocator<K>> class T>
bool hw5::HexAdapter<T>::isEndHelper(T<T<Cell> > &tempBoard,int row, int column){
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