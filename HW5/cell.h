#ifndef cell
#define cell
enum HEXCELL:char{
    userX = 'x',
    userO = 'o',
    empty = '-',
    goneX = 'X',
    goneO = 'O',
};
namespace hw5{
    class Cell{
    public:
        void setCell(int row, int column, HEXCELL player);
        void setCell(int row, char column);
        void setCell(HEXCELL player);
        HEXCELL getPlayer() const;
        int getRow()const;
        int getColumn()const;
        bool operator==(const Cell& other) const;
        bool operator!=(const Cell& other)const;
    private:
        int row,column;
        HEXCELL player;
    };
}
#endif