#ifndef array1d
#define array1d
using namespace std;
namespace hw5{
    class HexArray1D : public AbstractHex{
    public:
        HexArray1D();
        HexArray1D(const HEXCELL& player, const GAMETYPE& gameType, int size);
        HexArray1D(const HexArray1D& other);
        ~HexArray1D();
        const HexArray1D& operator=(const HexArray1D& other);
        void setSize(int) override;
        const Cell& operator()(int row ,int column) const override;
        Cell& operator()(int row ,int column) override;
        bool isEnd() override;
    private:
        bool isEndHelper(Cell *tempBoard,int row, int column);
        void displayBoard(const Cell *board);
        Cell *hexCells;
    };
}
#endif