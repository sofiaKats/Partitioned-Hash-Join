#include <iostream>
#include <cstring>
using namespace std;

// each index of the hopscoth table has a value and a corresponding bitmap
class Index
{
private:
    int value;
    int* bitmap;
public:
    Index(const int value, const int H);
    ~Index();
};