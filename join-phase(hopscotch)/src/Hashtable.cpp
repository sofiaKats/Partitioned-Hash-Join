#include <iostream>
#include <cstdlib>
#include <cstring>
#include "math.h"
#include "Hashtable.h"
using namespace std;

Hashtable::Hashtable(int table_size, int depth){
    this->table_size = table_size;
    this->depth = depth;

    hashtable = new Index*[table_size];
    for (int i=0; i<table_size; i++)
        hashtable[i] = new Index();
}

int Hashtable::hash_function(int id){

    int i =2;
    int j =32;
    int hashed_value = (int) (id*2654435761 % (int)pow(i,j));

    hashed_value = hashed_value >> (32-depth); 
}

void Hashtable::print_hashtable() {
    cout << "FINAL HASHTABLE: " << endl;
    for(int bucket=0; bucket<table_size; bucket++) cout << "   " << hashtable[bucket]->get_value();
    
    cout << endl << "\n Corresponding bitmaps: " << endl;
    for(int bucket=0; bucket<table_size; bucket++) {
        cout << "BUCKET " << bucket << " with value:  " <<  hashtable[bucket]->get_value() << " : ";
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

bool Hashtable::hopscotch_hatching(int** mock_data) {
    // for every number in the mock_data array
    for (int counter=0; counter<10; counter++) {
        int x = mock_data[counter][0]; // store value of mock data
        int i = mock_data[counter][1]; // store pseudo hash value of number
        cout << "New element to be inserted is: " << x << endl;
        //1. Check if bitmap of position i is full, if yes we rehash
        if(hashtable[i]->is_bitmap_full()) return true;           //THERE COULD BE A BETTER WAY

        //2. LINEAR SEARCH FOR EMPTY INDEX 
        int j = find_empty_index(i);
        
        //2.a) If(j==-1) tote o pinakas gematos, rehashing
        if(j==-1) { cout << "j is -1. That means table is full we need to rehash!" << endl;  return true; }        

        cout << "3" << endl;
        //3. While the empty index is not in the neighbourhood of j (H positions to the front)
        while( ((j-i) % table_size) >= H ) {
            cout << "4" << endl;
            int k=-1;
            // a) We find all H-1 positions that have values whose hash value k is in max H-1 distance from j
            int bucket;
            bool changed = false;
            for (bucket = j - (H-1); bucket<j; bucket++){
                int y = hashtable[bucket]->get_value();
                cout << "5" << endl;
                //checking each neighboring bucket's bitmap to find y's original hash value (k)
                int k=-1, position=bucket; 
                int loop_counter=0;

                int pos = (bucket + table_size)%table_size;
                for (int p = 0; p < H; p++){
                    if(hashtable[pos]->get_bitmap_index(loop_counter) == 1){
                        changed = true;
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
                    cout << "Now j is " << j << endl;
                    cout << "removed!\n";
                    break;  
                }
                else continue;
            }
            if (!changed) {
                cout << "No element y, table need rehashing!" << endl;
                return true;
            }  
        }
        add_value(j, x, i);
        cout << "8" << endl;
    }
    return false;
}

void Hashtable::resize(){
    int new_table_size = table_size*2;
    depth+=1;

    Index** hashtable_new = new Index*[new_table_size];
    for (int i=0; i<new_table_size; i++)
        hashtable_new[i] = new Index();

    for (int i=0; i<table_size; i++) delete hashtable[i];
    delete [] hashtable;

    this->hashtable = hashtable_new;
    this->table_size = new_table_size;
}

void Hashtable::Solve(int** mock_data){
    bool to_be_resized = hopscotch_hatching(mock_data);
    if (to_be_resized == true) {
        resize();
        cout << "Resized!" << endl;
        mock_data[11][0] = 17; mock_data[11][1] = 10;
        hopscotch_hatching(mock_data);
    }
    else cout << "\nAll good!" << endl;
}