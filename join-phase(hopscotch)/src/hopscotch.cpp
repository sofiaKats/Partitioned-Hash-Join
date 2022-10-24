#include <iostream>
#include <cstdlib>
#include <cstring>
#include "hopscotch.h"
using namespace std;

Index::Index() : has_value(false)
{
    bitmap = new int[H];
    // initializing bitmap with 0s
    for (int i=0; i<H; i++) bitmap[i] = 0;
}

Index::~Index()
{
    delete [] bitmap;
}

void Index::set_bitmap_index_to_1(const int index) { bitmap[index] = 1;}

void Index::set_bitmap_index_to_0(const int index) { bitmap[index] = 0; }

int Index::get_bitmap_index(const int index) { return bitmap[index]; }

bool Index::get_has_value(void) { return has_value; }

void Index::set_has_value(bool flag) { has_value = flag;}

void Index::set_value(const int val) { value = val; }

int  Index::get_value(void) { return value;}

void Index::print_bitmap(void) {
    for(int i=0; i<H; i++) cout << bitmap[i] ;
    cout << endl;
}

//returns true if full, false if not full
bool Index::is_bitmap_full(const int index) {
    for(int i=0; i<H; i++)
        if(bitmap[i] == 0) return false;
    return true;
}

void hopscotch_hatching(Index** hashtable, int** mock_data, int table_size) {
    // for every number in the mock_data array
    for (int counter=0; counter<8; counter++) {
        int x = mock_data[counter][0]; // store value of mock data
        int i = mock_data[counter][1]; // store pseudo hash value of number

        // if(hashtable[i].is_bitmap_full()) tote rehashing

        int j=-1; // linear search of array for empty space
        for(int bucket=i; bucket<table_size; bucket++)
            if(hashtable[bucket]->get_has_value() == false) j = bucket;

        // if(j==-1) tote o pinakas gematos, rehashing

        while( ((j-i) % table_size) >= H ) {
            
            for(int bucket=j-1; bucket>=(j-(H-1)); --bucket) {
                int y = hashtable[bucket]->get_value();
                //checking each neighboring bucket's bitmap to find y's original hash value (k)
                int k=-1, position=bucket; 
                int loop_counter=0;
                do {
                    if(hashtable[position]->get_bitmap_index(loop_counter) == 1) k = position;
                    --position;
                    ++loop_counter;
                } while(k!=-1 || position<(bucket-(H-1)));

                // if(k == -1) array is full
                if(k != -1) {
                    if(((j - k) % table_size) < H) {

                    }
                    //else array extention ??
                }
            }
        }

        hashtable[j]->set_value(x);
    }
}
