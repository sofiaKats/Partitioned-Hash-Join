#include <iostream>
#include <cstring>
#include "hopscotch.h"

using namespace std;

class Hashtable{
private:
    int table_size;
    Index** hashtable;
public:
    Hashtable(int);
    void hopscotch_hatching(int** mock_data);
    void print_hashtable();
};