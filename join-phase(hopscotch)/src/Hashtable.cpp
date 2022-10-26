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
    if (j==-1){
        //this means that from our point to the end of the table on the right, there are no free spots
        // but since we treat this hashtable as a cycle, we also check from the start of the table until tehe position i-1

        //COULD BE DONE MORE EFFICIENTLY WITH MOD!
        for(int bucket=0; bucket<i-1; bucket++)
        {
            cout << "2" << endl;
            if(hashtable[bucket]->get_has_value() == false){
                j = bucket;
                break;
            }
        }
    }
    return j;
}

void Hashtable::add_value(int pos, int value, int hash_value){
    hashtable[pos]->set_value(value);
    hashtable[pos]->set_has_value(true);

    //update bitmaps
    int indx;
    int loop = 0;
    for (int i = pos; i > pos- H; i--){
        indx = (i+table_size) %table_size;
        if (hash_value == indx) {
            if (value == 46) cout << "Pos is " << i << endl;
            hashtable[indx]->set_bitmap_index_to_1(loop);
        }
        else hashtable[indx]->set_bitmap_index_to_0(loop);
        loop++;
    }
}

void Hashtable::remove_value(int pos, int value, int hash_value ){
    //update bitmaps
    int loop = 0;
    int indx;
    for (int i = pos; i > pos- H; i--){
        indx = (i+table_size) %table_size;
        if (hash_value == indx) {
            hashtable[indx]->set_bitmap_index_to_0(loop);
        }
        loop++;
    } 
    hashtable[pos]->set_value(0);
    hashtable[pos]->set_has_value(false); 
}

void Hashtable::hopscotch_hatching(int** mock_data) {
    // for every number in the mock_data array
    for (int counter=0; counter<10; counter++) {
        int x = mock_data[counter][0]; // store value of mock data
        int i = mock_data[counter][1]; // store pseudo hash value of number
        cout << "New element to be inserted is: " << x << endl;
        //1. if(hashtable[i].is_bitmap_full()) tote rehashing

        //2. LINEAR SEARCH FOR EMPTY INDEX 
        int j = find_empty_index(i);
        
        // if(j==-1) tote o pinakas gematos, rehashing
        if(j==-1) {cout << "j is -1." << endl; break;}

        cout << "3" << endl;
        //3. While (j−i) mod n ≥ H
        while( ((j-i) % table_size) >= H ) {
            cout << "4" << endl;
            int k=-1;
            for (int bucket = j - (H-1); bucket<j; bucket++){
            //for(int bucket=j-1; bucket>=(j-(H-1)); --bucket) {
                int y = hashtable[bucket]->get_value();
                cout << "5" << endl;
                //checking each neighboring bucket's bitmap to find y's original hash value (k)
                int k=-1, position=bucket; 
                int loop_counter=0;

                int pos = (bucket + table_size)%table_size;
                for (int p = 0; p < H; p++){
                    if(hashtable[pos]->get_bitmap_index(loop_counter) == 1){
                        k = (pos + p + table_size)%table_size;
                        cout << "POSITION IS " << pos << " and value is " << hashtable[k]->get_value() << endl;
                        break;                        
                    }
                    loop_counter++;
                }

                if (k!=-1){    
                    //we move y to j, and making an empty spot !!
                    add_value(j, hashtable[k]->get_value(), temp_find_hash(hashtable[k]->get_value(), mock_data));
                    cout << "added\n";
                    remove_value(k, hashtable[k]->get_value(), temp_find_hash(hashtable[k]->get_value(), mock_data));
                    j = k;
                    cout << "removed!\n";
                    break;  
                }
                else continue;
            }     
        }
        add_value(j, x, i);
        cout << "8" << endl;
    }
}

