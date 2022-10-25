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
    int find_empty_index(int);
    void add_value(int, int, int);
    void remove_value(int, int, int);
    void update_bitmaps(int);
    void hopscotch_hatching(int** mock_data);
    void print_hashtable();
};