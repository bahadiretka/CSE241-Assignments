#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<random>
#include<algorithm>
#include"header.h"

 Hex::Hex(){
     // with default constructor size and game type not set.
    ifSizeSet = false;
    ifTypeSet = false;
    ifUserSet = false;
    markedCells = 0;
    incrementNumberOfGames();
};
Hex::Hex(const int& size){
    markedCells=0;
    setSize(size);
    incrementNumberOfGames();
}
Hex::Hex(const int& size, const int& gameType){
    markedCells=0;
    setGameType(gameType);
    setSize(size);
    incrementNumberOfGames();
}
Hex::Hex(const int&size, const int& gameType, const char& player){
    markedCells=0;
    setGameType(gameType);
    setSize(size);
    setUser(player);
    incrementNumberOfGames();
}

void Hex::playGame(){
    
    if(!ifSizeSet){
        setSize();
        setVectorSize();
        fillHexBoard();
        displayHexBoard();
    }
    if(!ifTypeSet) setGameType(); 
    if(!ifUserSet) setUser();
    if(gameType == 1)
        userToUser();
    if(gameType == 2)
        userToComputer();
}

void Hex::setSize(const int& size){
    
    if(size > 5){
        boardSize = size;
        setVectorSize();
        fillHexBoard();
        ifSizeSet = true;
    }
    else{
        std::cerr << "invalid size!\n" << "The object has created but size could not set!\n"; 
    }
}
void Hex::setSize(){
    int size;
    do{
        std::cout << "\nPlease enter size of Hex Game Table (SxS) (The range starts with 6) ->";
       std::cin >> size;
        while (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "\nInvalid input. Please try to input only integer values ->";
            std::cin >> size;
        }
        if(size < 6) std::cerr << "\nSize should be bigger than 5!\n";
    }while(size <= 5);
    
    boardSize = size;
    ifSizeSet = true;
}
void Hex::setVectorSize(){  
   hexCells.resize(boardSize);
   for(int i=0; i< boardSize ; i++) hexCells[i].resize(boardSize);
}
void Hex::fillHexBoard(){
    for(int row=0 ; row < boardSize; row++){
        for(int col=0; col < boardSize ; col++){
            hexCells[row][col].setCell(row,col,empty);
        }
    }
}
void Hex::Cell::setCell(int row, int column, char player){
    this->row = row;
    this->column = column;
    this->player = player;
}
void Hex::Cell::showCell() const{
    std::cout << player;
}
void Hex::displayHexBoard() const{
    
    std::cout << "\n\t\t";
    for(char c='a'; c-'a'<boardSize; c++) std::cout << ' ' << c ;
    std::cout << std::endl;
    
    for(int i=0; i< boardSize; i++){
        std::cout << "\t\t";
        if(i < 9) 
            for(int k=0; k < i; k++) std::cout << ' ';      
        else 
            for(int k=0; k < i-1; k++) std::cout << ' ';
            
        std::cout << i+1 << ' ';
        for(int j=0; j<boardSize ; j++){
            hexCells[i][j].showCell();
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}
void Hex::displayHexBoard(const std::vector<std::vector<Hex::Cell> > &board)const{
    std::cout << "\n\t\t";
    for(char c='a'; c-'a'<boardSize; c++) std::cout << ' ' << c ;
    std::cout << std::endl;
    
    for(int i=0; i< boardSize; i++){
        std::cout << "\t\t";
        if(i < 9) 
            for(int k=0; k < i; k++) std::cout << ' ';      
        else 
            for(int k=0; k < i-1; k++) std::cout << ' ';
            
        std::cout << i+1 << ' ';
        for(int j=0; j<boardSize ; j++){
            board[i][j].showCell();
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}
void Hex::setUser(){
    int user;
    std::cout << "\nPlease Select which user will you be?\n";
    std::cout << "\nUser(x)(horizontal):(1) User(o)(vertical) :(2) ->";
    
    do{
        std::cin >> user;
        while (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "\nInvalid input. Please try to input only integer values ->";
            std::cin >> user;
        }
        if(!(user == 1 || user == 2)) std::cerr << "Please select valid user! ->" ;
    }while(!(user == 1 || user == 2));
    if(user == 1){
        playingUser = user_x;
        otherUser = user_o;
    }
    if(user == 2){
        playingUser = user_o;
        otherUser = user_x;
    }
    ifUserSet = true;
}
void Hex::setUser(const char& player){
    if(player == user_x){
        playingUser = user_x;
        otherUser = user_o;
        ifUserSet =true;
    }
    else if(player == user_o){
        playingUser = user_o;
        otherUser = user_x;
        ifUserSet = true;
    }
    else{
        std::cerr << "Invalid user!!\n" << "The object has created but users could not set!!\n";
    }
}
bool Hex::userToUser(){

    Hex::Cell temp;
    while(true){
        displayHexBoard();
        temp = play();
        if(checkWinner() || isQuit(temp)) break;
        changeUser();
    }
}
bool Hex::userToComputer(){
 
    Hex::Cell temp;
    while(true){
        displayHexBoard();
        temp = play();
        if(checkWinner() || isQuit(temp)) break;
        changeUser();
        play(temp);
        if(checkWinner()) break;
        changeUser();
    }
}
bool Hex::isQuit(const Hex::Cell& c){
    return(c.getRow()==-1 && c.getColumn()==-1 && c.getCell() =='q');
}
void Hex::setGameType(){
    int type;
    do{
        std::cout << "\nWill you play with user(1) or computer(2) ->";
        std::cin >> type;
        while (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "\nInvalid input. Please try to input only integer values ->";
            std::cin >> type;
        }
        if(!(type == 1 || type == 2)) std::cerr << "\nPlease select user(1) or computer(2)!\n";
    }while(!(type == 1 || type == 2));
    gameType = type;
    ifTypeSet = true;
}
void Hex::setGameType(const int& gameType){
    if(gameType == 1 || gameType ==2){
        this->gameType = gameType;
        ifTypeSet=true;
    }
    else std::cerr << "Invalid game type!\n" << "The object has created but game type could not set!!\n";
}
Hex::Cell Hex::play(){
    // get input from the user like user1,user2 command quit from one object, jump the another object etc.
    Hex::Cell temp;
    bool inputFlag = false;
    std::string input;
    std::cout << "User " << playingUser << " plays\nPlease enter row and column ->";

    do{
        input.clear();
        std::getline(std::cin >> std::ws,input);

        if(input.length() <= 3){ // this might be user command
            int row,column;
            if(input.length() == 3){
                row = ((input[0] - '0')*10 + input[1] - '0') - 1; 
                column = input[2] - 'a';
            }
            if(input.length() == 2){
                row = (input[0] - '0') - 1;
                column = input[1] - 'a';
            }

            if(row >= 0 && row < boardSize && column >= 0 && column < boardSize){
                temp.setCell(row,column,playingUser);
                if(isEmpty(temp)){
                    hexCells[row][column] = temp;
                    incrementMarkedCell();
                    TotalMarkedCell++;
                    std::cout << "User " << playingUser << " just moved" << '(' << row + 1 << ',' << static_cast<char>(column + 'a')  << ')' << '\n';   
                    inputFlag = true;
                }
                else{
                    std::cout << "\nInputted location is full!\n" << "Please try to input empty cell location ->"; 
                }
            }
            else{
                std::cout << "\nThere is no cell inputted!\n" << "Please try to input valid cell location ->";
            }
        }
        else{ // this might be load or save command
            std::size_t found = input.find("LOAD");
            if(found != std::string::npos){
                std::string str = input.substr(5,input.length());
                inputFlag = loadGame(str);
            }
            found = input.find("SAVE");
            if(found != std::string::npos){
                std::string str = input.substr(5,input.length());
                inputFlag = saveGame(str);
                
            }
            found = input.find("quit");
            if(found != std::string::npos){
                temp.setCell(-1,-1,'q');
                inputFlag = true;
            }
        }
 
    }while(!inputFlag);   

    return temp;
}
void Hex::play(const Cell& c){
    if(playingUser == user_x) playForX(c);
    if(playingUser == user_o) playForO(c);
}
void Hex::playForO(const Cell& c){
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,boardSize-1);
    bool flag = false; 
    int temp_r , temp_c;

    if(c.getColumn() + 1 < boardSize && hexCells[c.getRow()][c.getColumn()+1].getCell() == empty && hexCells[c.getRow()][c.getColumn()+1].getCell() != otherUser){
     
            hexCells[c.getRow()][c.getColumn()+1].setCell(c.getRow(),c.getColumn()+1,playingUser) ;
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow()+1 << ',' << static_cast<char>(c.getColumn() + 'a' + 1) << ')' << std::endl;
        
    }
    else if(c.getColumn() -1 >= 0 && hexCells[c.getRow()][c.getColumn()-1].getCell() == empty && hexCells[c.getRow()][c.getColumn()-1].getCell() != otherUser){
            hexCells[c.getRow()][c.getColumn()-1].setCell(c.getRow(),c.getColumn()-1,playingUser);
            incrementMarkedCell(); 
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow()+1 << ',' << static_cast<char>(c.getColumn() + 'a' + -1) << ')' << std::endl;
    }
    else if(c.getRow()-1 >= 0 && c.getColumn() + 1 < boardSize && hexCells[c.getRow()-1][c.getColumn()+1].getCell() == empty && hexCells[c.getRow()-1][c.getColumn()+1].getCell() != otherUser){
            hexCells[c.getRow()-1][c.getColumn()+1].setCell(c.getRow()-1,c.getColumn()+1,playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow() << ',' << static_cast<char>(c.getColumn() + 'a' + 1) << ')' << std::endl;
    }

    else if(c.getRow()+1 < boardSize && hexCells[c.getRow()+1][c.getColumn()].getCell() == empty && hexCells[c.getRow()+1][c.getColumn()].getCell() != otherUser){
            hexCells[c.getRow()+1][c.getColumn()].setCell(c.getRow()+1,c.getColumn(),playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow()+2 << ',' << static_cast<char>(c.getColumn() + 'a')<< ')' << std::endl;
    }

    else if(c.getRow()-1 >= 0 && hexCells[c.getRow()-1][c.getColumn()].getCell() == empty && hexCells[c.getRow()-1][c.getColumn()].getCell() != otherUser){
            hexCells[c.getRow()-1][c.getColumn()].setCell(c.getRow()-1,c.getColumn(),playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow() << ',' << static_cast<char>(c.getColumn() + 'a')<< ')' << std::endl;
    }

    else if(c.getRow()+1 < boardSize && c.getColumn() - 1 >= 0 && hexCells[c.getRow()+1][c.getColumn()-1].getCell() == empty && hexCells[c.getRow()+1][c.getColumn()-1].getCell() != otherUser){
            hexCells[c.getRow()+1][c.getColumn()-1].setCell(c.getRow()+1,c.getColumn()-1,playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow()+2 << ',' << static_cast<char>(c.getColumn() + 'a' -1) << ')' << std::endl;
    }
    else{
        while(!flag){
            temp_r = distribution(generator);
            temp_c = distribution(generator);
            if(hexCells[temp_r][temp_c].getCell() == empty && hexCells[temp_r][temp_c].getCell() != otherUser){
                hexCells[temp_r][temp_c].setCell(temp_r,temp_c,playingUser);
                incrementMarkedCell();
                TotalMarkedCell++;
                flag = true;
            }
        }
        std::cout << "\nComputer just moved (" << temp_r + 1 << ',' << static_cast<char>(temp_c+'a') << ')' << std::endl;
    }
}
void Hex::playForX(const Cell& c){
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,boardSize-1);
    bool flag = false; 
    int temp_r , temp_c;

    if(c.getRow() + 1 < boardSize && hexCells[c.getRow()+1][c.getColumn()].getCell() == empty && hexCells[c.getRow()+1][c.getColumn()].getCell() != otherUser){
     
            hexCells[c.getRow()+1][c.getColumn()].setCell(c.getRow()+1,c.getColumn(),playingUser) ;
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow()+2 << ',' << static_cast<char>(c.getColumn() + 'a') << ')' << std::endl;
        
    }
    else if(c.getRow() -1 >= 0 && hexCells[c.getRow()-1][c.getColumn()].getCell() == empty && hexCells[c.getRow()-1][c.getColumn()].getCell() != otherUser){
            hexCells[c.getRow()-1][c.getColumn()].setCell(c.getRow()-1,c.getColumn(),playingUser); 
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow() << ',' << static_cast<char>(c.getColumn() + 'a') << ')' << std::endl;
    }
    else if(c.getRow()-1 >= 0 && c.getColumn() + 1 < boardSize && hexCells[c.getRow()-1][c.getColumn()+1].getCell() == empty && hexCells[c.getRow()-1][c.getColumn()+1].getCell() != otherUser){
            hexCells[c.getRow()-1][c.getColumn()+1].setCell(c.getRow()-1,c.getColumn()+1,playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow() << ',' << static_cast<char>(c.getColumn() + 'a' + 1) << ')' << std::endl;
    }

    else if(c.getRow()+1 < boardSize && hexCells[c.getRow()+1][c.getColumn()].getCell() == empty && hexCells[c.getRow()+1][c.getColumn()].getCell() != otherUser){
            hexCells[c.getRow()+1][c.getColumn()].setCell(c.getRow()+1,c.getColumn(),playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow()+2 << ',' << static_cast<char>(c.getColumn() + 'a')<< ')' << std::endl;
    }

    else if(c.getRow()-1 >= 0 && hexCells[c.getRow()-1][c.getColumn()].getCell() == empty && hexCells[c.getRow()-1][c.getColumn()].getCell() != otherUser){
            hexCells[c.getRow()-1][c.getColumn()].setCell(c.getRow()-1,c.getColumn(),playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow() << ',' << static_cast<char>(c.getColumn() + 'a')<< ')' << std::endl;
    }

    else if(c.getRow()+1 < boardSize && c.getColumn() - 1 >= 0 && hexCells[c.getRow()+1][c.getColumn()-1].getCell() == empty && hexCells[c.getRow()+1][c.getColumn()-1].getCell() != otherUser){
            hexCells[c.getRow()+1][c.getColumn()-1].setCell(c.getRow()+1,c.getColumn()-1,playingUser);
            incrementMarkedCell();
            TotalMarkedCell++;
            std::cout << "\nComputer just moved (" << c.getRow()+2 << ',' << static_cast<char>(c.getColumn() + 'a' -1) << ')' << std::endl;
    }
    else{
        while(!flag){
            temp_r = distribution(generator);
            temp_c = distribution(generator);
            if(hexCells[temp_r][temp_c].getCell() == empty && hexCells[temp_r][temp_c].getCell() != otherUser){
                hexCells[temp_r][temp_c].setCell(temp_r,temp_c,playingUser);
                incrementMarkedCell();
                TotalMarkedCell++;
                flag = true;
            }
        }
        std::cout << "\nComputer just moved (" << temp_r + 1 << ',' << static_cast<char>(temp_c+'a') << ')' << std::endl;
    }
}
bool Hex::checkWinner(){
    std::vector<std::vector<Hex::Cell> > tempBoard;
    tempBoard = hexCells;
    bool winFlag = false;
    if(playingUser == user_x){
        for(int i=0 ;i<boardSize ;i++) winFlag = winFlag || checkWinner(tempBoard,0+i,0);

    }
    if(playingUser == user_o){

        for(int i=0 ;i<boardSize ;i++) winFlag = winFlag || checkWinner(tempBoard,0,0+i);
    }
    if(winFlag){
        displayHexBoard(tempBoard);
        std::cout << "\n\t\tGame Over!\n" << "User " << playingUser << " WON!!\n";
    }
    return winFlag;
}
bool Hex::checkWinner(std::vector<std::vector<Hex::Cell> > &tempBoard,int row, int column){
    if(row >= 0 && row < boardSize && column >= 0 && column < boardSize){ // check it is in grid or not
        
        if(tempBoard[row][column].getCell() == playingUser){
            if(playingUser == user_x) tempBoard[row][column].setCell(row,column,gone_x);
            if(playingUser == user_o) tempBoard[row][column].setCell(row,column,gone_o);
            if(playingUser == user_x && column == boardSize -1) 
                return true;
            if(playingUser == user_o && row == boardSize -1)
                return true;
            else 
                return checkWinner(tempBoard,row-1,column+1) || checkWinner(tempBoard,row,column+1) || checkWinner(tempBoard,row+1,column) || checkWinner(tempBoard,row-1,column)||checkWinner(tempBoard,row+1,column-1)|| checkWinner(tempBoard,row,column-1);
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
void Hex::changeUser(){
    char temp;
    temp = playingUser;
    playingUser = otherUser;
    otherUser = temp;
}
bool Hex::saveGame(const std::string filename){

    bool flag = false;

    std::size_t f = filename.find(".txt");
    if(f!= std::string::npos){
        std::fstream file;
        file.open(filename.c_str(),std::ios::out);
            if(file.is_open()){
                file << boardSize;
                file << playingUser;
                file << otherUser;
                file << getMarkedCell();
                for(int i=0; i<boardSize ; i++){
                    for(int j=0; j<boardSize ; j++){
                            file.write((char*)&hexCells[i][j],sizeof(Hex::Cell));
                    }
                }
                flag = true;
                changeUser();
                std::cout << "Game saved to " << filename << '\n';
                file.close();
            }
            else{
                std::cerr << "\nFile could not opened!\n";
            }
                        
    }
    else{
            std::cerr << "\nFile format should be .txt !!\n";
    }
    return flag;
} 
bool Hex::loadGame(const std::string filename){

    bool flag=false;
    int tempMarked;
    std::size_t f = filename.find(".txt");
        if(f!= std::string::npos){
            std::fstream file;
            file.open(filename.c_str(),std::ios::in);
            if(file.is_open()){
                file >> boardSize;
                setVectorSize();
                file >> playingUser;
                file >> otherUser;
                file >> tempMarked;
                for(int i=0; i<boardSize ; i++){
                    for(int j=0; j<boardSize ; j++){
                        file.read((char*)&hexCells[i][j],sizeof(Hex::Cell));
                    }
                }
                    flag = true;
                    TotalMarkedCell -= getMarkedCell();
                    markedCells = tempMarked;
                    TotalMarkedCell += markedCells;
                    changeUser();
                    std::cout << "Game loaded from " << filename << '\n';
                    file.close();
            }
            else{
                std::cerr << "\nFile could not opened!\n";
            }
                        file.close();
        }
        else{
            std::cerr << "\nFile format should be .txt !!\n";
        }
        return flag;
}
bool Hex::compareHexBoards(const Hex& other)const { // compareHexBoard member function ignores equality because of instruction.
    return getMarkedCell() > other.getMarkedCell();
}
void Hex::setTotalMarkedCell(){
    TotalMarkedCell-=getMarkedCell();
}
