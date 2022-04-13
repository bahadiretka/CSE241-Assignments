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
    hexCells = nullptr;
    moves = nullptr;
    incrementNumberOfGames();
};
Hex::Hex(const int& size){
    markedCells=0;
    setSize(size);
    incrementNumberOfGames();
}
Hex::Hex(const int& size, const GAMETYPE& gameType){
    markedCells=0;
    setGameType(gameType);
    setSize(size);
    incrementNumberOfGames();
}
Hex::Hex(const int&size, const GAMETYPE& gameType, const HEXCELL& player){
    markedCells=0;
    setGameType(gameType);
    setSize(size);
    setUser(player);
    incrementNumberOfGames();
}
// copy constructor
Hex::Hex(const Hex& obj){
    incrementNumberOfGames();
    if(obj.ifSizeSet){
        this -> ifSizeSet = obj.ifSizeSet;
        this->boardSize = obj.boardSize;
        setBoardSize();
        // copying hex board to this hex board.
        for(int i=0; i<boardSize ; ++i){
            for(int j=0 ; j< boardSize; ++j){
                this->hexCells[i][j] = obj.hexCells[i][j];
            }
        }
        this->markedCells = obj.markedCells;
        setMove();
        for(int i=0; i<markedCells ; ++i) moves[i] = obj.moves[i];
        
        TotalMarkedCell += this -> markedCells;
    }
    else{
        this -> ifSizeSet = false;
        markedCells = 0;
    }
    if(obj.ifUserSet){
        this -> ifUserSet = obj.ifUserSet;
        this->playingUser = obj.playingUser;
        this->otherUser = obj.otherUser;
    }
    else{
        this -> ifUserSet = false;
    }
    if(obj.ifTypeSet){
        this -> ifTypeSet = obj.ifTypeSet;
        this -> gameType = obj.gameType;
    }
    else{
        this -> ifTypeSet = false;
    }
}
// assignment operator 
const Hex& Hex::operator=(const Hex& other){
    if(this == &other) // if someone does obj=obj
        return *this;
    
    if(hexCells != nullptr){
        for(int i=0; i< this -> boardSize ; ++i) delete [] hexCells[i];
        delete [] hexCells;
    }
    TotalMarkedCell -= this -> markedCells;
    this -> boardSize = other.boardSize;
    this ->playingUser = other.playingUser;
    this -> otherUser = other.otherUser;
    this -> ifUserSet = other.ifUserSet;
    this -> ifSizeSet = other.ifSizeSet;
    this -> gameType = other.gameType;
    this -> ifTypeSet = other.ifTypeSet;
    this -> markedCells = other.markedCells;
    TotalMarkedCell += this -> markedCells;
    setBoardSize(); // allocate memory for new board size
    for(int i=0; i<boardSize ; ++i){
        for(int j=0 ; j< boardSize; ++j){
            this->hexCells[i][j] = other.hexCells[i][j];
        }
    }
    if(this -> moves != nullptr)delete [] this -> moves;
    setMove();
    for(int i=0; i<this->markedCells ; ++i) moves[i] = other.moves[i];
    
    return *this;
}
Hex::~Hex(){
    if(hexCells != nullptr){
        for(int i=0; i<boardSize; ++i) delete[] hexCells[i];
        delete[] hexCells;
    }
    if(moves != nullptr) delete [] moves;
    TotalMarkedCell -= markedCells;
    numberOfGames--; 
}

void Hex::setSize(const int& size){
    
    if(size > 5){
        boardSize = size;
        setBoardSize();
        fillHexBoard();
        setMove();
        ifSizeSet = true;
    }
    else{
        std::cerr << "invalid size!\n";
        exit(-1); 
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
void Hex::setBoardSize(){
    hexCells = new Hex::Cell*[boardSize];
    for(int i=0; i< boardSize ; ++i) hexCells[i] = new Hex::Cell[boardSize];
}
void Hex::fillHexBoard(){
    for(int row=0 ; row < boardSize; ++row){
        for(int col=0; col < boardSize ; ++col){
            hexCells[row][col].setCell(row,col,empty);
        }
    }
}
void Hex::Cell::setCell(int row, int column, HEXCELL player){
    this->row = row;
    this->column = column;
    this->player = player;
}
void Hex::Cell::setCell(int row,char column){
    this->row = row-1;
    this->column = column - 'a';
}
void Hex::Cell::setCell(HEXCELL player) {this -> player = player;}


void Hex::displayHexBoard(Hex::Cell ** board)const{
    std::cout << "\n\t\t";
    for(char c='a'; c-'a'<boardSize; c++) std::cout << ' ' << c ;
    std::cout << std::endl;
    
    for(int i=0; i< boardSize; ++i){
        std::cout << "\t\t";
        if(i < 9) 
            for(int k=0; k < i; k++) std::cout << ' ';      
        else 
            for(int k=0; k < i-1; k++) std::cout << ' ';
            
        std::cout << i+1 << ' ';
        for(int j=0; j<boardSize ; ++j){
            std::cout << static_cast<char> (board[i][j].getPlayer());
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
        playingUser = userX;
        otherUser = userO;
    }
    if(user == 2){
        playingUser = userO;
        otherUser = userX;
    }
    ifUserSet = true;
}
void Hex::setUser(const HEXCELL& player){
    if(player == userX){
        playingUser = userX;
        otherUser = userO;
        ifUserSet =true;
    }
    else if(player == userO){
        playingUser = userO;
        otherUser = userX;
        ifUserSet = true;
    }
    else{
        std::cerr << "Invalid user!!\n";
        exit(-1);
    }
}

bool Hex::isQuit(const Hex::Cell& c){
    return(c.getRow()==-1 && c.getColumn()==-1 && c.getPlayer() ==goneX);
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
        if(!(type == userVSuser || type == userVScomputer)) std::cerr << "\nPlease select user(1) or computer(2)!\n";
    }while(!(type == userVSuser || type == userVScomputer));
    gameType = static_cast<GAMETYPE> (type);
    ifTypeSet = true;
}
void Hex::setGameType(const GAMETYPE& gameType){
    if(gameType == userVScomputer || gameType ==userVSuser){
        this->gameType = gameType;
        ifTypeSet=true;
    }
    else{
        std::cerr << "Invalid game type!\n";
        exit(-1);
    }
}
void Hex::playGame(){
    
    if(!ifSizeSet){
        setSize();
        setBoardSize();
        fillHexBoard();
        setMove();
        std::cout << *this;
    }
    if(!ifTypeSet) setGameType(); 
    if(!ifUserSet) setUser();
    if(gameType == userVSuser)
        userToUser();
    if(gameType == userVScomputer)
        userToComputer();
}
void Hex::userToUser(){
    Hex::Cell temp;
    while(!checkWinner()){
        std::cout << *this;
        temp = getInput();
        if(isQuit(temp)) break;
        if(checkInput(temp)){
            play(temp);
        }
       if(score(userX) > score(userO)) std::cout << "\nBoard is better for player X\n";
       else if(score(userO) > score(userX)) std::cout << "\nBoard is better for player O\n";
       else std::cout << "\nBoard is same for both user\n";
    }
}
void Hex::userToComputer(){
 
    Hex::Cell temp;
    HEXCELL tempUser;
    while(!checkWinner()){
        tempUser = playingUser;
        std::cout << *this;
        temp = getInput();
        if(isQuit(temp)) break;
        if(checkInput(temp)){
            play(temp);
            if(tempUser != playingUser) 
                play(); // if user played valid location then playing user will be changed
        }
        if(score(userX) > score(userO)) std::cout << "\nBoard is better for player X\n";
        else if(score(userO) > score(userX)) std::cout << "\nBoard is better for player O\n";
        else std::cout << "\nBoard is same for both user\n";
    }
}
Hex::Cell Hex::getInput(){
    Hex::Cell temp;
    bool inputFlag = false;
    std::string input;
    std::cout << "User " << static_cast<char> (playingUser) << " plays\nPlease enter row and column ->";
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
            inputFlag = true;
            temp.setCell(row,column,playingUser);
        }
        else{ // this might be load or save command
            std::size_t found = input.find("pre-undo");
            if(found != std::string::npos){
                --(*this);
                inputFlag=true;
                temp.setCell(-1,-1,empty);
                std::cout << "\nThe game is undone one move\n";
            }
            found = input.find("post-undo");
            if(found != std::string::npos){
                (*this)--;
                inputFlag = true;    
                temp.setCell(-1,-1,empty);
                std::cout << "\nThe game is undone one move\n";
            }
            found = input.find("LOAD");
            if(found != std::string::npos){
                std::string str = input.substr(5,input.length());
                temp.setCell(-1,-1,empty);
                inputFlag = loadGame(str);
            }
            found = input.find("SAVE");
            if(found != std::string::npos){
                std::string str = input.substr(5,input.length());
                temp.setCell(-1,-1,empty);
                inputFlag = saveGame(str);
                
            }
            found = input.find("quit");
            if(found != std::string::npos){
                temp.setCell(-1,-1,goneX);
                inputFlag = true;
            }
        }
        if(inputFlag == false) std::cout << "Invalid input!\n"; 
    }while(!inputFlag);   
    return temp;
}
bool Hex::checkInput(const Hex::Cell& c){
    return !(c.getRow() == -1 && c.getColumn() == -1 && c.getPlayer() == empty);
}

void Hex::play(const Hex::Cell& c){
    // get input from the user like user1,user2 command quit from one object, jump the another object etc.
    if(!ifUserSet){
        std::cerr << "\nUser is not set!\n";
        exit(-1);
    }
    if(c.getRow() >= 0 && c.getRow() < boardSize && c.getColumn() >= 0 && c.getColumn() < boardSize){
        if(isEmpty(c)){
            hexCells[c.getRow()][c.getColumn()].setCell(c.getRow(),c.getColumn(),playingUser);
            incrementMarkedCell();
            addMove(c);
            TotalMarkedCell++;
            std::cout << "User " << static_cast<char> (playingUser) << " just moved" << '(' << c.getRow() + 1 << ',' << static_cast<char>(c.getColumn() + 'a')  << ')' << '\n';
            changeUser();   
        }
        else{
            std::cout << "\nInputted location is full!\n" << "Please try to input empty cell location!\n"; 
        }
    }
    else{
        std::cout << "\nThere is no cell inputted!\n" << "Please try to input valid cell location!\n";
    }
        
}
Hex::Cell Hex::play(){
    if(!ifUserSet){
        std::cerr << "\nUser is not set!\n";
        exit(-1);
    }
    if(playingUser == userX) return playForX();
    if(playingUser == userO) return playForO();
}
bool Hex::isEmpty(const Hex::Cell& c){
    return (hexCells[c.getRow()][c.getColumn()].getPlayer() == empty);
}
Hex::Cell Hex::playForO(){
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,boardSize-1);
    bool flag = false; 
    int temp_r , temp_c;
    Hex::Cell reCell;
    auto lastMove = moves[markedCells-1];
    if(lastMove.getColumn() + 1 < boardSize && hexCells[lastMove.getRow()][lastMove.getColumn()+1].getPlayer() == empty && hexCells[lastMove.getRow()][lastMove.getColumn()+1].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow(),lastMove.getColumn()+1,playingUser);
    }
    else if(lastMove.getColumn() -1 >= 0 && hexCells[lastMove.getRow()][lastMove.getColumn()-1].getPlayer() == empty && hexCells[lastMove.getRow()][lastMove.getColumn()-1].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow(),lastMove.getColumn()-1,playingUser);
    }
    else if(lastMove.getRow()-1 >= 0 && lastMove.getColumn() + 1 < boardSize && hexCells[lastMove.getRow()-1][lastMove.getColumn()+1].getPlayer() == empty && hexCells[lastMove.getRow()-1][lastMove.getColumn()+1].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn()+1,playingUser);
    }

    else if(lastMove.getRow()+1 < boardSize && hexCells[lastMove.getRow()+1][lastMove.getColumn()].getPlayer() == empty && hexCells[lastMove.getRow()+1][lastMove.getColumn()].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn(),playingUser);
    }

    else if(lastMove.getRow()-1 >= 0 && hexCells[lastMove.getRow()-1][lastMove.getColumn()].getPlayer() == empty && hexCells[lastMove.getRow()-1][lastMove.getColumn()].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn(),playingUser);
    }

    else if(lastMove.getRow()+1 < boardSize && lastMove.getColumn() - 1 >= 0 && hexCells[lastMove.getRow()+1][lastMove.getColumn()-1].getPlayer() == empty && hexCells[lastMove.getRow()+1][lastMove.getColumn()-1].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn()-1,playingUser);
    }
    else{
        while(!flag){
            temp_r = distribution(generator);
            temp_c = distribution(generator);
            if(hexCells[temp_r][temp_c].getPlayer() == empty && hexCells[temp_r][temp_c].getPlayer() != otherUser){
                reCell.setCell(temp_r,temp_c,playingUser);
                flag = true;
            }
        }
    }
    hexCells[reCell.getRow()][reCell.getColumn()].setCell(reCell.getRow(),reCell.getColumn(),playingUser);
    incrementMarkedCell();
    addMove(reCell);
    TotalMarkedCell++;
    changeUser();
    std::cout << "\nComputer just moved (" << reCell.getRow()+1 << ',' << static_cast<char>(reCell.getColumn() + 'a') << ')' << std::endl;
    return reCell;
}
Hex::Cell Hex::playForX(){
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,boardSize-1);
    bool flag = false; 
    int temp_r , temp_c;
    Hex::Cell reCell;
    auto lastMove= moves[markedCells-1];
    if(lastMove.getRow() + 1 < boardSize && hexCells[lastMove.getRow()+1][lastMove.getColumn()].getPlayer() == empty && hexCells[lastMove.getRow()+1][lastMove.getColumn()].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn(),playingUser);        
    }
    else if(lastMove.getRow() -1 >= 0 && hexCells[lastMove.getRow()-1][lastMove.getColumn()].getPlayer() == empty && hexCells[lastMove.getRow()-1][lastMove.getColumn()].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn(),playingUser);
    }
    else if(lastMove.getRow()-1 >= 0 && lastMove.getColumn() + 1 < boardSize && hexCells[lastMove.getRow()-1][lastMove.getColumn()+1].getPlayer() == empty && hexCells[lastMove.getRow()-1][lastMove.getColumn()+1].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn()+1,playingUser);
    }

    else if(lastMove.getRow()+1 < boardSize && hexCells[lastMove.getRow()+1][lastMove.getColumn()].getPlayer() == empty && hexCells[lastMove.getRow()+1][lastMove.getColumn()].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn(),playingUser);
    }

    else if(lastMove.getRow()-1 >= 0 && hexCells[lastMove.getRow()-1][lastMove.getColumn()].getPlayer() == empty && hexCells[lastMove.getRow()-1][lastMove.getColumn()].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn(),playingUser);
    }

    else if(lastMove.getRow()+1 < boardSize && lastMove.getColumn() - 1 >= 0 && hexCells[lastMove.getRow()+1][lastMove.getColumn()-1].getPlayer() == empty && hexCells[lastMove.getRow()+1][lastMove.getColumn()-1].getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn()-1,playingUser);
    }
    else{
        while(!flag){
            temp_r = distribution(generator);
            temp_c = distribution(generator);
            if(hexCells[temp_r][temp_c].getPlayer() == empty && hexCells[temp_r][temp_c].getPlayer() != otherUser){
                reCell.setCell(temp_r,temp_c,playingUser);
                flag = true;
            }
        }
    }
    hexCells[reCell.getRow()][reCell.getColumn()].setCell(reCell.getRow(),reCell.getColumn(),playingUser);
    incrementMarkedCell();
    addMove(reCell);
    TotalMarkedCell++;
    changeUser();
    std::cout << "\nComputer just moved (" << reCell.getRow()+1 << ',' << static_cast<char>(reCell.getColumn() + 'a') << ')' << std::endl;
    return reCell;
}
bool Hex::checkWinner(){
    decltype(hexCells) tempBoard;
    tempBoard = new Hex::Cell*[boardSize];
    for(int i=0; i<boardSize ;++i) tempBoard[i] = new Hex::Cell[boardSize];
    copyBoard(tempBoard);
    bool winFlag = false;
    if(otherUser == userX){
        for(int i=0 ;i<boardSize ;++i){
            winFlag = winFlag || checkWinner(tempBoard,0+i,0);
        }
    }
    if(otherUser == userO){
        for(int i=0 ;i<boardSize ;++i){
            winFlag = winFlag || checkWinner(tempBoard,0,0+i);
        }
    }
    if(winFlag){
        displayHexBoard(tempBoard);
        std::cout << "\n\t\tGame Over!\n" << "User " << static_cast<char> (otherUser) << " WON!!\n";
    }
    for(int i=0; i<boardSize ;++i) delete [] tempBoard[i];
    delete [] tempBoard;

    return winFlag;
}
bool Hex::checkWinner(Hex::Cell ** tempBoard,int row, int column){
    if(row >= 0 && row < boardSize && column >= 0 && column < boardSize){ // check it is in grid or not
        
        if(tempBoard[row][column].getPlayer() == otherUser){
            if(otherUser == userX){
                tempBoard[row][column].setCell(row,column,goneX);
            }
            if(otherUser == userO){
                tempBoard[row][column].setCell(row,column,goneO);
            }
            if(otherUser == userX && column == boardSize -1) 
                return true;
            if(otherUser == userO && row == boardSize -1)
                return true;

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
    HEXCELL temp;
    temp = playingUser;
    playingUser = otherUser;
    otherUser = temp;
}
bool Hex::saveGame(const std::string filename){

    bool flag = false;
    std::size_t f = filename.find(".txt");
    if(f!= std::string::npos){
        std::ofstream file;
        file.open(filename.c_str(),std::ios::out);
            if(file.is_open()){
                file << *this;
                flag = true;
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
            std::ifstream file;
            file.open(filename.c_str(),std::ios::in);
            if(file.is_open()){
                    file >> *this;
                    flag = true;
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
bool Hex::operator==(const Hex& other) const{
    return getMarkedCell() == other.getMarkedCell();
}
bool Hex::operator>(const Hex& other) const{
    return getMarkedCell() > other.getMarkedCell();
}
bool Hex::operator<(const Hex& other) const{
    return getMarkedCell() < other.getMarkedCell();
}
void Hex::copyBoard(Hex::Cell **tempBoard){

    for(int i=0; i<boardSize; ++i){
        for(int j=0; j<boardSize; ++j){
            tempBoard[i][j] = hexCells[i][j];
        }
    }
}
void Hex::setMove(){
    moves = new Hex::Cell[boardSize*boardSize];
}
void Hex::addMove(const Hex::Cell &com){
    moves[markedCells-1] = com;
}
const Hex& Hex::operator--(){
    if(markedCells > 0){
        hexCells[moves[markedCells-1].getRow()][moves[markedCells-1].getColumn()].setCell(empty);
        markedCells--;
        TotalMarkedCell--;
        changeUser();
        return *this;
    }
    else{
        std::cerr << "Illegal operator usage. Program terminated.\nnote:The board was initial board!\n";
        exit(-1);
    }
}
const Hex Hex::operator--(int){
    if(markedCells > 0){
        Hex temp;
        temp = *this;
        hexCells[moves[markedCells-1].getRow()][moves[markedCells-1].getColumn()].setCell(empty);
        markedCells--;
        TotalMarkedCell--;
        changeUser();
        return temp;
    }
    else{
        std::cerr << "Illegal operator usage. Program terminated.\nnote:The board was initial board!\n";
        exit(-1);
    }
}
std::ostream& operator<<(std::ostream& out,const Hex& obj){

    out << "\n\t\t";
    for(char c='a'; c-'a'<obj.getSize(); c++) out << ' ' << c ;
    out << '\n';
    
    for(int i=0; i< obj.getSize(); ++i){
        out << "\t\t";
        if(i < 9) 
            for(int k=0; k < i; k++) std::cout << ' ';      
        else 
            for(int k=0; k < i-1; k++) std::cout << ' ';
            
        std::cout << i+1 << ' ';
        for(int j=0; j<obj.getSize() ; ++j){
            out << static_cast<char> (obj.hexCells[i][j].getPlayer());
            out << ' ';
        }
        out << '\n';
    }
    return out;
}
std::ofstream& operator<<(std::ofstream& outFile,const Hex& obj){
    outFile.write((char*)&obj.boardSize,sizeof(int));
    outFile.write((char*)&obj.playingUser,sizeof(int));
    outFile.write((char*)&obj.otherUser,sizeof(int));
    outFile.write((char*)&obj.markedCells,sizeof(int));
        for(int i=0; i<obj.boardSize ; ++i){
            for(int j=0; j<obj.boardSize ; ++j){
                    outFile.write((char*)&obj.hexCells[i][j],sizeof(Hex::Cell));
            }
        }
        for(int i=0; i<obj.getMarkedCell() ; ++i) outFile.write((char*)&obj.moves[i],sizeof(Hex::Cell)); 

    return outFile;
}
std::ifstream& operator>>(std::ifstream& inFile,Hex& obj){
    int tempMarked;
    if(obj.hexCells != nullptr){
        for(int i=0; i<obj.boardSize; ++i) delete [] obj.hexCells[i];
        delete [] obj.hexCells;
    }
    inFile.read((char*)&obj.boardSize,sizeof(int));
    obj.setBoardSize();
    inFile.read((char*)&obj.playingUser,sizeof(int));
    inFile.read((char*)&obj.otherUser,sizeof(int));
    inFile.read((char*)&tempMarked,sizeof(int));

        for(int i=0; i<obj.boardSize ; ++i){
            for(int j=0; j<obj.boardSize ; ++j){
                inFile.read((char*)&obj.hexCells[i][j],sizeof(Hex::Cell));
            }
        }
   
        Hex::TotalMarkedCell -= obj.getMarkedCell();
        obj.markedCells = tempMarked;
        if(obj.moves != nullptr) delete [] obj.moves;
        obj.setMove();
        for(int i=0; i<obj.getMarkedCell() ; ++i) inFile.read((char*)&obj.moves[i],sizeof(Hex::Cell)); 
        Hex::TotalMarkedCell += obj.markedCells;
    return inFile;
}
int Hex::score(HEXCELL player){
    decltype(hexCells) tempBoard;
    tempBoard = new Hex::Cell*[boardSize];
    for(int i=0; i<boardSize ;++i) tempBoard[i] = new Hex::Cell[boardSize];
    int highScoreX,highScoreO;
    highScoreX = highScoreO = 0;

    int tempScore=0;
    int tempRow,tempColumn;
    if(player == userX){
        for(int row=0; row<boardSize; ++row){
            copyBoard(tempBoard);
            for(int col=0; col<boardSize; ++col){
                scoreX = 0;
                score(tempBoard,row,col,player);
                if(scoreX > 1){
                    tempScore+=scoreX; 
                }
            }
            if(highScoreX < tempScore) highScoreX = tempScore;
            tempScore=0;
        }
    }
    if(player == userO){
        for(int col=0; col<boardSize; ++col){
            copyBoard(tempBoard);
            for(int row=0; row<boardSize; ++row){
                scoreO = 0;
                score(tempBoard,row,col,player);
                if(scoreO > 1){
                    tempScore+=scoreO; 
                }
            }
            if(highScoreO < tempScore) highScoreO = tempScore;
            tempScore=0;
        }
    }
    scoreX = highScoreX;
    scoreO = highScoreO; 
    for(int i=0; i<boardSize ;++i) delete [] tempBoard[i];
    delete [] tempBoard;
    
    if(player==userX) return scoreX;
    if(player==userO) return scoreO;

}
void Hex::score(Hex::Cell **tempBoard,int row, int column, HEXCELL player){
    if(row >= 0 && row < boardSize && column >= 0 && column < boardSize){ // check it is in grid or not
        
        if(tempBoard[row][column].getPlayer() == player){
            if(player == userX){
                tempBoard[row][column].setCell(row,column,goneX);
                scoreX++;
            }
            if(player == userO){
                tempBoard[row][column].setCell(row,column,goneO);
                scoreO++;
            }
    
                if(player == userX){
                    score(tempBoard,row-1,column+1,player);
                    score(tempBoard,row,column+1,player);
                }
                if(player == userO){
                    score(tempBoard,row+1,column-1,player);
                    score(tempBoard,row+1,column,player);
                
                }
        }
    }
}

