#include <iostream>
#include <cstring>
#include "hopscotch.h"

using namespace std;

class Hashtable{
private:
    int table_size;
    int depth;
    Index** hashtable;
public:
    Hashtable(int, int);
    int hash_function(int);
    int find_empty_index(int);
    void add_value(int, int, int);
    void remove_value(int, int, int);
    void resize();           //temporary argument
    bool hopscotch_hatching(int**);
    void print_hashtable();
    void Solve(int**);
};