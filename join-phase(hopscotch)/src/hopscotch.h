#include <iostream>
#include <cstring>
using namespace std;

#define H 3 

// each index of the hopscoth table has a value and a corresponding bitmap
class Index
{
private:
    int value;
    bool has_value; //flag to check if position is empty
    int* bitmap;
public:
    Index();
    ~Index();
    void set_bitmap_index_to_1(const int index); 
    void set_bitmap_index_to_0(const int index); 
    int  get_bitmap_index(const int index);
    void print_bitmap(void);
    bool get_has_value(void);
    void set_has_value(bool flag);
    void set_value(const int val);
    int  get_value(void);
    bool is_bitmap_full(const int index); //returns true if full, false if not full
};


// given an empty hashtable and an array of data
// perform hopscotch hashing
void hopscotch_hatching(Index** hashtable, int** mock_data, int table_size);