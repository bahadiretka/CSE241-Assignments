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

using namespace std;
void hw5::AbstractHex::play(){
    if(playingUser == userX) playForX();
    if(playingUser == userO) playForO();
    changeUser();    
}
void hw5::AbstractHex::playForX(){
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,getBoardSize()-1);
    bool flag = false; 
    int temp_r , temp_c;
    hw5::Cell reCell;
    auto lastMove= moves[markedCells-1];
    if(lastMove.getRow() + 1 < getBoardSize() && (*this)(lastMove.getRow()+1,lastMove.getColumn()).getPlayer() == empty && (*this)(lastMove.getRow()+1,lastMove.getColumn()).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn(),playingUser);        
    }
    else if(lastMove.getRow() -1 >= 0 && (*this)(lastMove.getRow()-1,lastMove.getColumn()).getPlayer() == empty && (*this)(lastMove.getRow()-1,lastMove.getColumn()).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn(),playingUser);
    }
    else if(lastMove.getRow()-1 >= 0 && lastMove.getColumn() + 1 < getBoardSize() && (*this)(lastMove.getRow()-1,lastMove.getColumn()+1).getPlayer() == empty && (*this)(lastMove.getRow()-1,lastMove.getColumn()+1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn()+1,playingUser);
    }

    else if(lastMove.getRow()+1 < getBoardSize() && lastMove.getColumn() - 1 >= 0 && (*this)(lastMove.getRow()+1,lastMove.getColumn()-1).getPlayer() == empty && (*this)(lastMove.getRow()+1,lastMove.getColumn()-1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn()-1,playingUser);
    }

    else if(lastMove.getColumn()+1 < getBoardSize() && (*this)(lastMove.getRow(),lastMove.getColumn()+1).getPlayer() == empty && (*this)(lastMove.getRow(),lastMove.getColumn()+1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow(),lastMove.getColumn()+1,playingUser);
    }

    else if(lastMove.getColumn() - 1 >= 0 && (*this)(lastMove.getRow(),lastMove.getColumn()-1).getPlayer() == empty && (*this)(lastMove.getRow(),lastMove.getColumn()-1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow(),lastMove.getColumn()-1,playingUser);
    }
    else{
        while(!flag){
            temp_r = distribution(generator);
            temp_c = distribution(generator);
            if((*this)(temp_r,temp_c).getPlayer() == empty && (*this)(temp_r,temp_c).getPlayer() != otherUser){
                reCell.setCell(temp_r,temp_c,playingUser);
                flag = true;
            }
        }
    }
    (*this)(reCell.getRow(),reCell.getColumn()).setCell(reCell.getRow(),reCell.getColumn(),playingUser);
    incrementMarkedCell();
    moves.push_back(reCell);
    cout << "\nComputer just moved (" << reCell.getRow()+1 << ',' << static_cast<char>(reCell.getColumn() + 'a') << ')' << endl;    
}
void hw5::AbstractHex::playForO(){
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,getBoardSize()-1);
    bool flag = false; 
    int temp_r , temp_c;
    Cell reCell;
    auto lastMove = moves[markedCells-1];
    if(lastMove.getColumn() + 1 < getBoardSize() && (*this)(lastMove.getRow(),lastMove.getColumn()+1).getPlayer() == empty && (*this)(lastMove.getRow(),lastMove.getColumn()+1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow(),lastMove.getColumn()+1,playingUser);
    }
    else if(lastMove.getColumn() -1 >= 0 && (*this)(lastMove.getRow(),lastMove.getColumn()-1).getPlayer() == empty && (*this)(lastMove.getRow(),lastMove.getColumn()-1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow(),lastMove.getColumn()-1,playingUser);
    }
    else if(lastMove.getRow()-1 >= 0 && lastMove.getColumn() + 1 < getBoardSize() && (*this)(lastMove.getRow()-1,lastMove.getColumn()+1).getPlayer() == empty && (*this)(lastMove.getRow()-1,lastMove.getColumn()+1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn()+1,playingUser);
    }

    else if(lastMove.getRow()+1 < getBoardSize() && (*this)(lastMove.getRow()+1,lastMove.getColumn()).getPlayer() == empty && (*this)(lastMove.getRow()+1,lastMove.getColumn()).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn(),playingUser);
    }

    else if(lastMove.getRow()-1 >= 0 && (*this)(lastMove.getRow()-1,lastMove.getColumn()).getPlayer() == empty && (*this)(lastMove.getRow()-1,lastMove.getColumn()).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()-1,lastMove.getColumn(),playingUser);
    }

    else if(lastMove.getRow()+1 < getBoardSize() && lastMove.getColumn() - 1 >= 0 && (*this)(lastMove.getRow()+1,lastMove.getColumn()-1).getPlayer() == empty && (*this)(lastMove.getRow()+1,lastMove.getColumn()-1).getPlayer() != otherUser){
            reCell.setCell(lastMove.getRow()+1,lastMove.getColumn()-1,playingUser);
    }
    else{
        while(!flag){
            temp_r = distribution(generator);
            temp_c = distribution(generator);
            if((*this)(temp_r,temp_c).getPlayer() == empty && (*this)(temp_r,temp_c).getPlayer() != otherUser){
                reCell.setCell(temp_r,temp_c,playingUser);
                flag = true;
            }
        }
    }
    (*this)(reCell.getRow(),reCell.getColumn()).setCell(reCell.getRow(),reCell.getColumn(),playingUser);
    incrementMarkedCell();
    moves.push_back(reCell);
    cout << "\nComputer just moved (" << reCell.getRow()+1 << ',' << static_cast<char>(reCell.getColumn() + 'a') << ')' << endl;
}
void hw5::AbstractHex::play(const Cell& c){
    if(c.getRow() >= 0 && c.getRow() < getBoardSize() && c.getColumn() >= 0 && c.getColumn() < getBoardSize()){
        if((*this)(c.getRow(),c.getColumn()).getPlayer() == empty){
            (*this)(c.getRow(),c.getColumn()).setCell(c.getRow(),c.getColumn(),playingUser);
            incrementMarkedCell();
            moves.push_back(c);
            cout << "User " << static_cast<char> (playingUser) << " just moved" << '(' << c.getRow() + 1 << ',' << static_cast<char>(c.getColumn() + 'a')  << ')' << '\n';
            changeUser();   
        }
        else{
            cout << "\nInputted location is full!\n" << "Please try to input empty cell location!\n"; 
        }
    }
    else{
        cout << "\nThere is no cell inputted!\n" << "Please try to input valid cell location!\n";
    }    
}

void hw5::AbstractHex::print()const{
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
            cout << static_cast<char>((*this)(i,j).getPlayer());
            cout << ' ';
        }
        cout << endl;
    }
}
void hw5::AbstractHex::reset(){
    for(int row=0 ; row < getBoardSize(); row++){
        for(int col=0; col < getBoardSize() ; col++){
            (*this)(row,col).setCell(row,col,empty);
        }
    }
}
bool hw5::AbstractHex::writeToFile(const string filename){
    bool flag = false;

    size_t f = filename.find(".txt");
    if(f!= string::npos){
        fstream file;
        file.open(filename.c_str(),ios::out);
            if(file.is_open()){
                file << getBoardSize() << ' ';
                file << static_cast<char>(playingUser) << ' ';
                file << static_cast<char>(otherUser) << ' ';
                file << static_cast<int>(gameType) << ' ';
                file << markedCells;
                for(int i=0; i<getBoardSize() ; i++){
                    for(int j=0; j<getBoardSize() ; j++){
                            file << static_cast<char>((*this)(i,j).getPlayer());
                    }
                }
                for(int i=0; i<markedCells ;i++){
                        file.write((char*)&moves[i],sizeof(Cell));
                }
                flag = true;
                cout << "Game saved to " << filename << '\n';
                file.close();
            }
            else{
                cerr << "\nFile could not opened!\n";
            }
                        
    }
    else{
            cerr << "\nFile format should be .txt !!\n";
    }
    return flag;

}
bool hw5::AbstractHex::readFromFile(const string filename){
    bool flag=false;
    char t_playing;
    char temp;
    int t_game;
    size_t f = filename.find(".txt");
        if(f!= string::npos){
            fstream file;
            file.open(filename.c_str(),ios::in);
            if(file.is_open()){
                file >> boardSize;
                setSize(boardSize);
                file >> t_playing;
                playingUser = static_cast<HEXCELL>(t_playing);
                file >> t_playing;
                otherUser = static_cast<HEXCELL>(t_playing);
                file >> t_game;
                gameType = static_cast<GAMETYPE>(t_game);
                file >> markedCells;
                for(int i=0; i<getBoardSize() ; i++){
                    for(int j=0; j<getBoardSize() ; j++){
                        file.get(temp);
                        (*this)(i,j).setCell(i,j,static_cast<HEXCELL>(temp));
                    }
                }
                    moves.resize(markedCells);
                    for(int i=0; i<markedCells ;i++){
                        file.read((char*)&moves[i],sizeof(Cell));
                    }
                   
                    flag = true;
                    cout << "Game loaded from " << filename << '\n';
                    file.close();
            }
            else{
                cerr << "\nFile could not opened!\n";
            }
                        file.close();
        }
        else{
            cerr << "\nFile format should be .txt !!\n";
        }
        return flag;
}

void hw5::AbstractHex::playGame(){
    if(!ifSizeSet){
        getSizeFromUser();
        reset();
        print();
    }
    if(!ifTypeSet) getTypeFromUser(); 
    if(!ifUserSet) getUserFromUser();

    if(gameType == userVSuser){
        Cell temp;
        while(!isEnd()){
            print();
            temp = getInput();
            if(temp.getRow()==-1 && temp.getColumn()==-1 && temp.getPlayer() ==goneX) break;
            if(!(temp.getRow() == -1 && temp.getColumn() == -1 && temp.getPlayer() == empty)){
                play(temp);
            }
        }
    }
    if(gameType == userVScomputer){
        Cell temp;
        HEXCELL tempUser;
        while(!isEnd()){
            tempUser = playingUser;
            print();
            temp = getInput();
            if(temp.getRow()==-1 && temp.getColumn()==-1 && temp.getPlayer() ==goneX) break;
                if(!(temp.getRow() == -1 && temp.getColumn() == -1 && temp.getPlayer() == empty)){
                    play(temp);
                    if(tempUser != playingUser) 
                        play(); // if user played valid location then playing user will be changed
                }
        }
    }    
}
void hw5::AbstractHex::isThereMove()const throw(hw5::noMove){
    if(markedCells == 0) throw hw5::noMove();
}
bool hw5::AbstractHex::operator==(const hw5::AbstractHex& other) const{
    if(this->getBoardSize() != other.getBoardSize()) 
        return false;
    for(int i=0; i<getBoardSize();++i){
        for(int j=0; j<getBoardSize(); ++j){
            if((*this)(i,j) != other(i,j)){
                return false;
            }
        }
    }
    return true;
}
void hw5::AbstractHex::checkIndex(int row, int column) const throw(hw5::invalidIndex){
    if(!(row >=0 & row < getBoardSize() && column >= 0 && column < getBoardSize())){
        throw hw5::invalidIndex();
    }
}
void hw5::AbstractHex::displayMoves(){
    for(int i=0; i<markedCells; i++){
        cout << moves[i].getRow() + 1 << ' ' << static_cast<char> (moves[i].getColumn() + 'a') << static_cast<char>(moves[i].getPlayer()) << '\n';
    }
}
const hw5::Cell& hw5::AbstractHex::lastMove()const{
    try{
        isThereMove();
        return moves[markedCells-1];
    }
    catch(const hw5::noMove& e){
        cerr << e.what() << '\n';
    }
}
hw5::AbstractHex::AbstractHex(){
    ifUserSet = false;
    ifSizeSet = false;
    ifTypeSet = false;
    markedCells=0;
}
hw5::AbstractHex::AbstractHex(const HEXCELL& player, const GAMETYPE& gameType){
    markedCells = 0;
    setUser(player);
    setGameType(gameType);
}
void hw5::AbstractHex::setUser(const HEXCELL& player){
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
        cerr << "Invalid user!!\n";
        exit(-1);
    }
}
void hw5::AbstractHex::setGameType(const GAMETYPE& Type){
    
    if(Type == userVSuser || Type == userVScomputer){
        gameType = Type;
        ifTypeSet=true;
    }
    else{
        cerr << "Invalid game type!\n";
        exit(-1);
    }
}
hw5::Cell hw5::AbstractHex::getInput(){
    Cell temp;
    bool inputFlag = false;
    string input;
    cout << "User " << static_cast<char> (playingUser) << " plays\nPlease enter row and column ->";
    do{
        input.clear();
        getline(cin >> ws,input);

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
            
            size_t found = input.find("LOAD");
            if(found != string::npos){
                string str = input.substr(5,input.length());
                temp.setCell(-1,-1,empty);
                inputFlag = readFromFile(str);
            }
            found = input.find("SAVE");
            if(found != string::npos){
                string str = input.substr(5,input.length());
                temp.setCell(-1,-1,empty);
                inputFlag = writeToFile(str);
                
            }
            found = input.find("quit");
            if(found != string::npos){
                temp.setCell(-1,-1,goneX);
                inputFlag = true;
            }
        }
        if(inputFlag == false) cout << "Invalid input!\n"; 
    }while(!inputFlag);   
    return temp;
}
void hw5::AbstractHex::getSizeFromUser(){
    int size;
    do{
        cout << "\nPlease enter size of Hex Game Table (SxS) (The range starts with 6) ->";
        cin >> size;
        while (cin.fail()){
            cin.clear();
            cin.ignore();
            cerr << "\nInvalid input. Please try to input only integer values ->";
            cin >> size;
        }
        if(size < 6) cerr << "\nSize should be bigger than 5!\n";
    }while(size <= 5);
    boardSize = size;
    setSize(boardSize);
    ifSizeSet = true;
}
void hw5::AbstractHex::getUserFromUser(){
    int user;
    cout << "\nPlease Select which user will you be?\n";
    cout << "\nUser(x)(horizontal):(1) User(o)(vertical) :(2) ->";
    
    do{
        cin >> user;
        while (cin.fail()){
            cin.clear();
            cin.ignore();
            cerr << "\nInvalid input. Please try to input only integer values ->";
            cin >> user;
        }
        if(!(user == 1 || user == 2)) cerr << "Please select valid user! ->" ;

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
void hw5::AbstractHex::getTypeFromUser(){
    int type;
    do{
        cout << "\nWill you play with user(1) or computer(2) ->";
        cin >> type;
        while (cin.fail()){
            cin.clear();
            cin.ignore();
            cerr << "\nInvalid input. Please try to input only integer values ->";
            cin >> type;
        }
        if(!(type == userVSuser || type == userVScomputer)) cerr << "\nPlease select user(1) or computer(2)!\n";
    }while(!(type == userVSuser || type == userVScomputer));
    setGameType(static_cast<GAMETYPE>(type));
    ifTypeSet = true;
}
void hw5::AbstractHex::changeUser(){
    HEXCELL temp;
    temp = playingUser;
    playingUser = otherUser;
    otherUser = temp;
}