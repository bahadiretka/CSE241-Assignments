#ifndef hvector
#define hvector
using namespace std;
namespace hw5{
    class HexVector :public AbstractHex{
    public:
        HexVector();
        HexVector(const HEXCELL& player, const GAMETYPE& gameType, int size);
        void setSize(int) override;
        const Cell& operator()(int row ,int column) const override;
        Cell& operator()(int row ,int column) override;
        bool isEnd() override;
    private:
        bool isEndHelper(vector<vector<Cell> > &tempBoard,int row, int column);
        void displayBoard(const vector<vector<Cell> > &temp);
        vector<vector<Cell> > hexCells;
    };
}
#endif