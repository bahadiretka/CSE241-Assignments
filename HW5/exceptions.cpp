#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<random>
#include<algorithm>
#include<cstdlib>
#include<array>
#include<deque>
#include<exception>
#include"exceptions.h"
using namespace std;
using namespace hw5;

invalidIndex::invalidIndex():std::runtime_error("Invalid Index!!")
        {}
noMove::noMove():std::runtime_error("There is no move!")
    {}
    