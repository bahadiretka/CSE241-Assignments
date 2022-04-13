#include<iostream>
#include"cell.h"

using namespace std;
HEXCELL hw5::Cell::getPlayer() const{
    return player;
}
int hw5::Cell::getRow()const{
    return row;
}
int hw5::Cell::getColumn()const{
    return column;
}
void hw5::Cell::setCell(int row, int column, HEXCELL player){
    this->row = row;
    this->column = column;
    this->player = player;
}

void hw5::Cell::setCell(int row,char column){
    this->row = row-1;
    this->column = column - 'a';
}
void hw5::Cell::setCell(HEXCELL pl) {player = pl;}

bool hw5::Cell::operator==(const Cell& other) const{
    return (this->getRow() == other.getRow() && this->getColumn() == other.getColumn() && this->getPlayer() == other.getPlayer());
}
bool hw5::Cell::operator!=(const Cell& other) const{
    return !(*this == other);
}