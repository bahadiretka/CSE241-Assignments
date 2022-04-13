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
#include"exceptions.h"
#include"abstract.h"
#include"hvector.h"
#include"array1d.h"
#include"adapter.h"

using namespace std;
using namespace hw5;

bool globalController(AbstractHex *arr[], int numberOfObject);

int main (){
    AbstractHex *games[3];
    games[0] = new HexVector;
    games[1] = new HexArray1D;
    games[2] = new HexAdapter<deque>;
    games[0]->playGame();
    games[1]->playGame();
    games[2]->playGame();
    cout << globalController(games,3) << endl;

}
bool globalController(AbstractHex *arr[], int numberOfObject){
    for(int i=0; i<numberOfObject; ++i)
        if((*arr[i]).getBoardSize() < 6) return false;
    HEXCELL temp;
    for(int i=0; i<numberOfObject; ++i){
        for(int row=0; row<(*arr[i]).getBoardSize(); ++row){
            for(int col=0 ; col<(*arr[i]).getBoardSize(); ++col){
                temp = (*arr[i])(row,col).getPlayer();
                if(!(temp == userX || temp == userO || temp == empty || temp == goneX || temp == goneO))
                    return false;
            }
        }
    }
    return true;
}