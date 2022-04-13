#ifndef header
#define header
#include<vector>
#include<string>
enum HEXCELL:char{
    userX = 'x',
    userO = 'o',
    empty = '-',
    goneX = 'X',
    goneO = 'O',
};
enum GAMETYPE:int{
    userVSuser = 1,
    userVScomputer = 2,
};
class Hex{
public:
    class Cell{
    public:
        void setCell(int row, int column, HEXCELL player);
        void setCell(int row, char column);
        void setCell(HEXCELL player);
        inline HEXCELL getPlayer() const{return player;}
        inline int getRow()const{return row;}
        inline int getColumn()const{return column;}
    private:
        int row,column;
        HEXCELL player;
    };
    /* constructors */
    Hex();
    explicit Hex(const int& size);
    explicit Hex(const int& size, const GAMETYPE& gameType);
    explicit Hex(const int &size, const GAMETYPE& gameType,const HEXCELL& player);
    
        /* BIG THREE */
    Hex(const Hex& obj);
    ~Hex();
    const Hex& operator=(const Hex& other); // default assignment operator is not good.
        /* BIG THREE */
 
    /* overloaded operators */ 
    bool operator==(const Hex& other) const;
    bool operator>(const Hex& other) const;
    bool operator<(const Hex&other) const;
    const Hex& operator--(); // prefix decrement operator.
    const Hex operator--(int); // postfix decrement operator.
    friend std::ostream& operator<<(std::ostream& out,const Hex& obj); 
    friend std::ifstream& operator>>(std::ifstream& inFile, Hex& obj);
    friend std::ofstream& operator<<(std::ofstream &outFile,const Hex& obj);
    /* overloaded operators */ 
    
    /* setter,getter for static datas */
    inline static int getNumberOfGames(){return Hex::numberOfGames;}; // returns total active number of games.
    inline static void incrementNumberOfGames(){Hex::numberOfGames++;} //increments total number of games.
    inline static int nonEmpty(){return Hex::TotalMarkedCell;} // returns total marked cell number in all game 

    /*setter for private class datas */
    void setUser(); // sets the user.
    void setUser(const HEXCELL& player);
    void setGameType(); // sets the game type (user to user vs user to computer)
    void setGameType(const GAMETYPE& gameType); // sets game type while creating Hex object.
    void setSize(); // from the user gets size of cell vector
    void setSize(const int& size); // sets size of cell in the class
    void setBoardSize();  // allocates memory for hexCells.
    void fillHexBoard(); // fills hex board with empty cells.

    /* functions that plays the game */
    void playGame(); // plays the game until game is over.
    void play(const Cell& c); // plays user commmands with single step.
    Hex::Cell play(); // plays computer commands with single step.
    
    Hex::Cell getInput(); // gets input while playing a game.
    
    bool saveGame(const std::string filename); // saves game while playing game with SAVE file.txt input.
    bool loadGame(const std::string filename); // loads game while playing game with LOAD file.txt input.
    
    bool checkWinner(); // checks there is a winner or not.
    
    inline int getMarkedCell() const{return markedCells;} // returns private marked Cells
    inline int getSize() const {return boardSize;} // returns size of Hex Cell

    int score(HEXCELL player); // calculates and return score for user
    
private:
    void userToUser(); // plays  user to user game 
    void userToComputer(); // plays user to computer game 
    bool isEmpty(const Hex::Cell &c); // checks the coordinate is valid or not
    Hex::Cell playForX(); // plays computer for x
    Hex::Cell playForO(); // plays computer for o
    bool checkWinner(Hex::Cell ** tempBoard,int row, int column); // overloaded helper member function for checkWinner.
    void displayHexBoard(Hex::Cell ** board)const;  // display member function for outputing copied hexCells 2d array.
    void copyBoard(Hex::Cell **tempBoard);
    bool isQuit(const Hex::Cell& c); // checks while playing game if you input quit, quits from playing game 
    inline void incrementMarkedCell(){markedCells++;} // increments marked cell if input is valid.
    bool checkInput(const Hex::Cell& c); // checks the input cell is valid or not
    void changeUser(); // changes the user while playing game 
    void addMove(const Hex::Cell &com); // adds user or computer move at the end of the dynamic array marked Cell
    void setMove(); // allocates memory for commands.
    void score(Hex::Cell **tempBoard,int row, int column, HEXCELL player); // overloaded helper function.
    
    /* private Hex datas.*/
    HEXCELL playingUser,otherUser;
    GAMETYPE gameType;
    int scoreX,scoreO; 
    int markedCells; // holds non-empty cell number. 
    int boardSize;
    
    bool ifUserSet; // checker for user set or not
    bool ifSizeSet; //checker for size set or not
    bool ifTypeSet; // checker for type set or not
    
    static int TotalMarkedCell;
    static int numberOfGames;
    
    Hex::Cell **hexCells;
    Hex::Cell *moves; // it will hold the user or computer moves
};
#endif
