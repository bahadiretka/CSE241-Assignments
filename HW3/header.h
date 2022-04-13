#ifndef header
#define header
#include<vector>
#include<string>
enum h_c{
    user_x = 'x',
    user_o = 'o',
    empty = '-',
    gone_x = 'X',
    gone_o = 'O',
};

class Hex{
public:
    /* constructors */
    Hex();
    Hex(const int& size);
    Hex(const int& size, const int& gameType);
    Hex(const int &size, const int & gameType,const char& player);
    ~Hex(){
        numberOfGames--;
    }
    /* member functions */
    inline int getSize(){return hexCells.size();} // returns size of Hex Cell
    void setSize(); // from the user gets size of cell vector
    void setSize(const int& size); // sets size of cell in the class
    void displayHexBoard() const; // display the current board on the screen
    bool compareHexBoards(const Hex& other) const; // compare two hex boards
    inline static int getNumberOfGames(){return Hex::numberOfGames;}; // returns total active number of games.
    inline static void incrementNumberOfGames(){Hex::numberOfGames++;} //increments total number of games.
    inline static int nonEmpty(){return Hex::TotalMarkedCell;} // returns total marked cell number in all game 
    void playGame(); // if game created and not played or reset everything in data members call this func.
    bool saveGame(const std::string filename); // saves game while playing game with SAVE file.txt input.
    bool loadGame(const std::string filename); // loads game while playing game with LOAD file.txt input.
    void setUser(); // sets the user.
    void setUser(const char& player);
    void setVectorSize();  // sets vector size
    bool checkWinner(); // checks there is a winner or not.
    void fillHexBoard(); // fills hex board with empty cells.
    void setGameType(); // sets the game type (user to user vs user to computer)
    void setGameType(const int& gameType); // sets game type while creating Hex object.
    inline int getMarkedCell() const{return markedCells;} // returns private marked Cells
    inline void setHexNO(int n){HexNO =n;} //numerates hex object 
    inline int getHexNO(){return HexNO;} // returns numerated Hex number.
    void setTotalMarkedCell(); // sets total number of marked cells(important for deleting hex object)
private:
    class Cell{
    public:
        void setCell(int row, int column, char player);
        inline char getCell() const{return player;}
        void showCell() const;
        inline int getRow()const{return row;}
        inline int getColumn()const{return column;}
    private:
        int row,column;
        char player;
    };
    bool userToUser(); // plays  user to user game 
    bool userToComputer(); // plays user to computer game 
    inline bool isEmpty(const Cell &c){return (hexCells[c.getRow()][c.getColumn()].getCell() == empty);};
    Hex::Cell play(); // plays user commands
    void play(const Cell& c); // plays computer commmands
    void playForX(const Cell& c); // plays computer for x
    void playForO(const Cell& c); // plays computer for o
    bool checkWinner(std::vector<std::vector<Hex::Cell> > & tempBoard,int row, int column); // overloaded helper member function for checkWinner.
    void displayHexBoard(const std::vector<std::vector<Hex::Cell> > &board)const;  // overloaded display member function
    bool isQuit(const Hex::Cell& c); // checks while playing game if you input quit, quits from playing game 
    void changeUser(); // change the user while playing game 
    inline void incrementMarkedCell(){markedCells++;} // increments marked cell if input is valid.
    // private Hex datas.
    char playingUser;
    char otherUser;
    bool ifUserSet; // checker for user set or not
    int boardSize;
    bool ifSizeSet; //checker for size set or not
    int gameType;
    bool ifTypeSet; // checker for type set or not
    int markedCells;
    int HexNO;
    static int TotalMarkedCell;
    static int numberOfGames;
    std::vector<std::vector<Cell> > hexCells;
};
#endif
