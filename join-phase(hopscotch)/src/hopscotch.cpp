#include <iostream>
#include <cstdlib>
#include <cstring>
#include "hopscotch.h"
using namespace std;

Index::Index(const int value, const int H) : value(value)
{
    bitmap = new int[H];
}

Index::~Index()
{
    delete [] bitmap;
}
