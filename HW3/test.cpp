#include<iostream>
#include<string>
#include<vector>
#include"header.h"

int Hex::numberOfGames = 0;
int Hex::TotalMarkedCell = 0;

int main(){

    /* for testing two classes and 5 or more game at the same time, this is a test main function*/

    int gameNumber;
    int playingGame,choice;

    std::vector<Hex> games;
    std::cout << "\t\t\tWelcome To test Hex Game Menu\n\n";
    std::cout << "\nPlease enter how many game will be created? ->";
    std::cin >> gameNumber;
    games.resize(gameNumber);
    for(int i=0; i<gameNumber ;i++) games[i].setHexNO(i+1);
    std::cout << "You created " << gameNumber << " game\n";
    do{
        std::cout << "\n\n";
        for(int i=0; i<games.size() ;i++) std::cout << "\tGame " << games[i].getHexNO();
        std::cout << "\n\n1.Play Game\n2.Delete Game\n3.Show Non Empty Cells in All Games\n4.Show active number of games\n5.Compare two Hex Game\n->";
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
            for(int i=0; i<gameNumber ;i++){
                if(games[i].getHexNO() == playingGame){
                    found = i;
                    break;
                }
            }
            
            if(found != -1){
                    if(games[found].checkWinner()){
                        std::cout << "Game " << playingGame << " is over!!\n";
                    }
                    else{
                        games[found].playGame();
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
                for(d=0; d<gameNumber ; d++){
                    if(games[d].getHexNO() == del){
                        f = true;
                        break;
                    }
                }
                if(f){
                    games[d].setTotalMarkedCell(); 
                    games.erase(games.begin()+d); 
                    std::cout << "\nGame " << del << " Deleted!\n";
                    gameNumber--; // this is for main also there is static int total active game
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
            for(int i=0; i<gameNumber; i++){
                if(games[i].getHexNO() == firstGame){
                    c1=i;
                    f1=true;
                    break;
                }
            }
            for(int i=0; i<gameNumber ; i++){
                if(games[i].getHexNO()==secondGame){
                    c2=i;
                    f2=true;
                    break;
                }
            }
            if(f1 && f2){ // compareHexBoard member function ignores equality because of instruction.
                if(games[c1].compareHexBoards(games[c2])){
                    std::cout << "\nGame " << firstGame << " has more non-empty cell than Game " << secondGame << '\n';
                }
                else{
                    std::cout << "\nGame " << secondGame << " has more non-empty cell than Game " << firstGame << '\n';
                }
            }
            else{
                std::cerr << "\nPlease enter valid games for compare two boards!\n";
            }
        }
    }while(choice != -1);
   
    return 0;   
}
