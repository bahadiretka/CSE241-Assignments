#ifndef abstract
#define abstract
using namespace std;
using namespace hw5;
#include"exceptions.h"
enum GAMETYPE:int{
    userVSuser = 1,
    userVScomputer = 2,
};
namespace hw5{
    class AbstractHex{
    public:
        AbstractHex();
        AbstractHex(const HEXCELL& player, const GAMETYPE& gameType);
        virtual ~AbstractHex(){}; // there is no delete data
        bool readFromFile(const string filename);
        bool writeToFile(const string filename);
        void reset();
        virtual void setSize(int size)=0;
        void play(); // computer
        void play(const Cell&); // user
        virtual bool isEnd()=0;
        void print() const;
        virtual const Cell& operator()(int row ,int column) const =0;
        virtual Cell& operator()(int row ,int column) =0;
        void playGame(); // plays the game until the game end.
        bool operator==(const AbstractHex&) const;
        const Cell& lastMove() const;
        int numberOfMoves() const {return markedCells;}
        void setUser(const HEXCELL& player);
        void setGameType(const GAMETYPE& gameType);
        inline void incrementMarkedCell() {++markedCells;};
        inline int getBoardSize()const{return boardSize;};
        void displayMoves();
    protected:
        void playForX();
        void playForO();
        void checkIndex(int row,int column)const throw(invalidIndex);
        void isThereMove() const throw(noMove);
        Cell getInput();
        void getSizeFromUser();
        void getTypeFromUser();
        void getUserFromUser();
        void changeUser(); // change the user while playing game 
        int boardSize;
        bool ifUserSet; // checker for user set or not
        bool ifSizeSet; //checker for size set or not
        bool ifTypeSet; // checker for type set or not
        int markedCells; // holds non-empty cell number.
        HEXCELL playingUser,otherUser;
        GAMETYPE gameType;
        vector<Cell> moves; // it will hold the user or computer moves

    };
}
#endif