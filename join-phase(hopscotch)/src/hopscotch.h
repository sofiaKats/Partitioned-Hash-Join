#include <iostream>
#include <cstring>
using namespace std;

// each index of the hopscoth table has a value and a corresponding bitmap
class index
{
private:
    int value;
    int* bitmap;
public:
    index(const int value, const int H);
    ~index();
};