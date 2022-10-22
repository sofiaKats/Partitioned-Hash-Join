#include <iostream>
#include <cstring>
#include "hopscotch.h"
using namespace std;

index::index(const int value, const int H) : value(value)
{
    bitmap = new int[H];
}

index::~index()
{
    delete [] bitmap;
}
