#include <iostream>
#include <cstring>
#include "hopscotch.h"

using namespace std;

class Hashtable{
private:
    int emptySpaces;
    int table_size;
    int depth;
    Index** hashtable;

    int** mock_data;

    int findNeighborPosByK(int, int);
    bool checkHashtableFull();
    bool checkBitmapFull(int);
    bool insert(int, int);
    int findPos(int);
    int checkBucketBitmap(int, int&, bool&, int);
    int swapEmpty(int, int, int, int);
    int findSwapNeighbourPos(int);
    int slideLeft(int, int);
    int hash(int);
    int find_empty_index(int);
    void add_value(int, int, int);
    void remove_value(int, int, int);
    void resize();
    int findClosestPowerOf2(int);
public:
    //Hashtable(int, int, int**);
    Hashtable(int);
    void add(int, int);               
    void print_hashtable();
    void Solve();
};