#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Hashtable.h"
using namespace std;

Hashtable::Hashtable(int table_size){
    this->table_size = table_size;

    hashtable = new Index*[table_size];
    for (int i=0; i<table_size; i++)
        hashtable[i] = new Index();
}

void Hashtable::print_hashtable() {
    cout << "FINAL HASHTABLE: " << endl;
    for(int bucket=0; bucket<table_size; bucket++) cout << "   " << hashtable[bucket]->get_value();
    
    cout << endl << "\n Corresponding bitmaps: " << endl;
    for(int bucket=0; bucket<table_size; bucket++) {
        cout << "BUCKET " << bucket << " with value:  " <<  hashtable[bucket]->get_value() << " :\n";
        for (int bit=0; bit< H ; bit++)  cout << "  " << hashtable[bucket]->get_bitmap_index(bit);
        cout << endl;
    }
}

// HAVE TO CHANGE J AND K INITIAL VALUE, COULD BE -1 SOMETIMES
int Hashtable::find_empty_index(int i){
    int j=-1; // linear search of array for empty space
    for(int bucket=i; bucket<table_size; bucket++)
    {
        cout << "2" << endl;
        if(hashtable[bucket]->get_has_value() == false){
            j = bucket;
            break;
        }
    }
    return j;
}

void Hashtable::add_value(int pos, int value, int hash_value){
    hashtable[pos]->set_value(value);
    hashtable[pos]->set_has_value(true);

    //update bitmaps
    int loop = 0;
    for (int i = pos; ((i > pos- H) && (i>-1)); i--){
        if (hash_value == i) {
            hashtable[i]->set_bitmap_index_to_1(loop);
        }
        else hashtable[i]->set_bitmap_index_to_0(loop);
        loop++;
    }
}

void Hashtable::hopscotch_hatching(int** mock_data) {
    // for every number in the mock_data array
    for (int counter=0; counter<8; counter++) {
        int x = mock_data[counter][0]; // store value of mock data
        int i = mock_data[counter][1]; // store pseudo hash value of number
        cout << "1. New element to be inserted is: " << x << endl;
        //1. if(hashtable[i].is_bitmap_full()) tote rehashing

        //2. LINEAR SEARCH FPR EMPTY INDEX 
        int j = find_empty_index(i);
        
        // if(j==-1) tote o pinakas gematos, rehashing
        if(j==-1) {cout << "j is -1." << endl; break;}

        cout << "3" << endl;
        while( ((j-i) % table_size) >= H ) {
            cout << "4" << endl;
            for(int bucket=j-1; bucket>=(j-(H-1)); --bucket) {
                int y = hashtable[bucket]->get_value();
                cout << "5" << endl;
                //checking each neighboring bucket's bitmap to find y's original hash value (k)
                int k=-1, position=bucket; 
                int loop_counter=0;
                do {
                    cout << "6" << endl;
                    // starting from the current bucket going backwards in the array we have
                    // to check the bitmaps to find out the hash value of y.
                    // when we enter the loop the first time, (loop_counter=0) we have to check
                    // index=0 of the current bucket's bitmap, when the loop_counter=1 we check 
                    // the previous bucket's bitmap, specifically index=1 of this bitmap, loop=2 index=2 e.t.c
                    if(hashtable[position]->get_bitmap_index(loop_counter) == 1) {
                        cout << "POSITION IS " << position << " and value is " << hashtable[position]->get_value() << endl;
                        k = position;
                        break;
                    }
                    --position;
                    ++loop_counter;
                } while(k!=-1 || position<(bucket-(H-1)));

                
                // if(k == -1) array is full
                if(k != -1) {
                    if(((j - k) % table_size) < H) {
                        /*
                        cout << "7" << endl;
                        hashtable[j]->set_value(y);
                        hashtable[j]->set_has_value(true);
                        j=k-1;
                        hashtable[j]->set_has_value(false);
                        //update bitmaps of neighbor
                        hashtable[k]->set_bitmap_index_to_1(loop_counter);
                        hashtable[k]->set_bitmap_index_to_0(--loop_counter);
                        */
                       add_value(j, x, i);
                       j = k;
                    }
                    //else array extention ??
                }
            }           
        }
        add_value(j, x, i);
        cout << "8" << endl;
    }
}
