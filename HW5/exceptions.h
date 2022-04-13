#ifndef exceptions
#define exceptions
using namespace std;
namespace hw5{
    class invalidIndex:public runtime_error{
    public:
        invalidIndex();
    };
    class noMove: public runtime_error{
    public:
        noMove();
    };
}
#endif