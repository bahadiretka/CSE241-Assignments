#include<iostream>
#include<string>
#include<vector>
#include"header.h"
#include<fstream>
int Hex::numberOfGames = 0;
int Hex::TotalMarkedCell = 0;


// simple structure for can play multiple game at the same time.
struct MultipleHexGame{
    Hex game;
    int id;
};


int main(){
    

        /* for testing two classes and 5 or more game at the same time, this is a test main function*/


    int gameNumber;
    int playingGame,choice;
    std::vector<MultipleHexGame> GameArray; 

    std::cout << "\t\t\tWelcome To test Hex Game Menu\n\n";
    std::cout << "\nPlease enter how many game will be created? ->";
    std::cin >> gameNumber;
    GameArray.resize(gameNumber);
    for(int i=0; i<gameNumber ;++i) GameArray[i].id = i+1;
    std::cout << "You created " << gameNumber << " game\n";
    do{
        std::cout << "\n\n";
        for(int i=0; i<GameArray.size() ;++i) std::cout << "\tGame " << GameArray[i].id;
        std::cout << "\n\n1.Play Game\n2.Delete Game\n3.Show Non Empty Cells in All Games\n4.Show active number of games\n5.Compare two Hex Game\n";
        std::cout << "6.Get score for user\n->";
        std::cin >> choice;
        while (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "\nInvalid input. Please try to input only integer values ->";
            std::cin >> choice;
        }
        if(choice ==1){
            std::cout << "\n\nWhich game do you want to play ->";
            std::cin >> playingGame;
            int found=-1;
            for(int i=0; i<GameArray.size() ;++i){
                if(GameArray[i].id == playingGame){
                    found = i;
                    break;
                }
            }
            
            if(found != -1){
                    if(GameArray[found].game.checkWinner()){
                        std::cout << "Game " << playingGame << " is over!!\n";
                    }
                    else{
                        GameArray[found].game.playGame();
                    }
            }
            else{
                std::cout << "\nPlease enter valid game number!\n";
            }
        }
        if(choice == 2){
            int del;
            std::cout << "\nWhich game dou you want to delete? ->";
            std::cin >> del;
            
            if(del >= 1){
                // delete required game from vector;
                bool f = false;
                int d;
                for(d=0; d<GameArray.size() ; d++){
                    if(GameArray[d].id == del){
                        f = true;
                        break;
                    }
                }
                if(f){
                    GameArray.erase(GameArray.begin()+d); 
                    std::cout << "\nGame " << del << " Deleted!\n";
                }
                else{
                    std::cerr << "\nThere is no game for delete!\n";
                }           
            }
            else{
                std::cerr << "\nInvalid Game Number!\n";
            }
        }
        if(choice == 3){
            std::cout << "There are " << Hex::nonEmpty() << " marked Cell in all games\n";
        }
        if(choice == 4){
            std::cout << "There are " << Hex::getNumberOfGames() << " active games now\n";
        }
        if(choice == 5){
            int firstGame,secondGame;
            bool f1,f2;
            f1=f2=false;
            int c1,c2;
            // compares two hex game.
            std::cout << "\nwhich games do you want to compare?\n";
            std::cout << "First game ->";
            std::cin >> firstGame;
            std::cout << "Second game ->";
            std::cin >> secondGame;
            for(int i=0; i<GameArray.size(); ++i){
                if(GameArray[i].id == firstGame){
                    c1=i;
                    f1=true;
                    break;
                }
            }
            for(int i=0; i<GameArray.size() ; ++i){
                if(GameArray[i].id==secondGame){
                    c2=i;
                    f2=true;
                    break;
                }
            }
            if(f1 && f2){ // there are 3 comparing ovearloaded operators.
                if(GameArray[c1].game > GameArray[c2].game){
                    std::cout << "\nGame " << firstGame << " has more marked-cell than game " << secondGame << '\n';
                }
                if(GameArray[c1].game < GameArray[c2].game){
                    std::cout << "\nGame " << firstGame << " has smaller marked-cell than game " << secondGame << '\n';
                }
                if(GameArray[c1].game == GameArray[c2].game){
                    std::cout << "\nGame " << firstGame << " has same marked-cell with game " << secondGame << '\n';
                }
            }
            else{
                std::cerr << "\nPlease enter valid games for compare two boards!\n";
            }
        }
        if(choice == 6){
            std::cout << "Which game dou you want to get score? ->";
            int gameNo,i;
            bool isThere=false;
            std::cin >> gameNo;
                for(i=0; i<GameArray.size() ;++i){
                    if(GameArray[i].id == gameNo){
                        isThere = true;
                        break;
                    }
                }
            if(isThere){
                std::cout << "Which user do you want to get score(x or o)->";
                char user;
                std::cin >> user;
                if(user == userX || user == userO){
                    std::cout << "\nGame " << GameArray[i].id <<" User " << user << "'s score is " <<GameArray[i].game.score(static_cast<HEXCELL>(user));
                }
                else{
                    std::cout << "invalid user!\n";
                }
            }
            else{
                std::cout << "There is no game for get score!\n";
            }
        }
    }while(choice != -1);

/*  some usage of new features  */   

/*
    Hex game1,game2(7),game3(8,userVScomputer),game4(9,userVSuser,userX); // some usage of my constructor.

    Hex::Cell inputCell,rValFromPlay; // inner class is public now so it can be used for single step.

    //usage of some member function 
    game1.setSize(6);
    game1.setGameType(userVSuser);
    game1.setUser(userO);

    inputCell.setCell(2,'a');

    game1.play(inputCell); // plays for user single step
    
    for(int i=0 ; i<10 ; ++i){ // computer will play 10 step
        rValFromPlay=game1.play(); // it plays for computer single step
    }

    std::cout << game1;

    //usage of overloaded operators


    //pre-fix and post fix operators
    std::cout << "Before assigning game1 to game2 with using pre-fix operator\n";
    std::cout << "\n\n\n\n\t\tgame1\n" << game1;
    std::cout << "\n\t\tgame2\n" << game2; // stream extraction for ostream.
    
    game2 = --game1; // this is test or usage of pre-fix and assignment operator.

    std::cout << "After assigning game2 to game3 with using pre-fix operator\n";
    std::cout << "\n\t\tgame1\n" <<  game1;
    std::cout << "\n\t\tgame2\n" << game2;

    std::cout << "Before assigning game2 to game3 with using post-fix operator\n";
    std::cout << "\n\t\tgame2\n" << game2;
    std::cout << "\n\t\tgame3\n" << game3;

    game3 = game2--; // this is test or usage of post-fix and assignment operator.

    std::cout << "After assigning game2 to game3 with using post-fix operator\n";
    std::cout << "\n\t\tgame2\n" << game2;
    std::cout << "\n\t\tgame3\n" << game3;
    // pre-fix and post fix operators 

    // assignment operator and copy constructor 

    // assigment operator and copy constructor do not copy whole content of Hex objects 

    Hex game5 = game1; // copy constructor.

    std::cout << "\ngame5 created with copy constructor\n";
    std::cout << "\n\t\tgame1\n" << game1;
    std::cout << "\n\t\tgame5\n" << game5;
    // some changes on game5.
    game5--;
    game5--; 
    game5--;
    
    std::cout << "\n\nAfter some changes on game5\n";
    std::cout << "\n\t\tgame1\n" << game1;
    std::cout << "\n\t\tgame5\n" << game5;

    game1 = game5; // assignment operator

    std::cout << "\ngame5 assigned to game1\n";
    std::cout << "\n\t\tgame1\n" << game1;
    std::cout << "\n\t\tgame5\n" << game5;
    // some changes on game1.
    game1--;
    game1--; 
    game1--;
    
    std::cout << "\n\nAfter some changes on game1\n";
    std::cout << "\n\t\tgame1\n" << game1;
    std::cout << "\n\t\tgame5\n" << game5;

    // stream insertion and extraction operator for ifstream and ofstream 
    std::ofstream outFile;
    std::ifstream inFile;

    outFile.open("test.txt",std::ios::out);

        if(outFile.is_open()){
            std::cout << "game1 saving to test.txt";
            std::cout << "\n\t\tgame1\n" << game1;
            outFile << game1;
    
        }
        else{
            std::cerr << "File could not opened!\n";
        }
    outFile.close();

    inFile.open("test.txt",std::ios::in);

        if(inFile.is_open()){
            std::cout << "file is loading from test.txt to game4\n";
            inFile >> game4;
            std::cout << "\n\t\tgame4\n" << game4;
        }
        else{
            std::cerr << "File could not opened!\n";
        }

    inFile.close();

        if(game1 > game4){
            std::cout << "game1 has more marked-Cells than game4\n";
        }
        if(game1 < game4){
            std::cout << "game1 has smaller marked-Cells than game4\n";
        }
        if(game1 == game4){
            std::cout << "game1 and game4 has same marked-Cells\n";
        }
*/
    return 0;   
}

