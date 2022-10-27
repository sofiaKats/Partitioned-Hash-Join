#include <iostream>
#include <cstdlib>
#include <cstring>
#include "math.h"
#include "Hashtable.h"
using namespace std;

Hashtable::Hashtable(int table_size, int depth, int** mock_data){
    this->emptySpaces = table_size;
    this->table_size = table_size;
    this->depth = depth;

    hashtable = new Index*[table_size];
    for (int i=0; i<table_size; i++)
        hashtable[i] = new Index();

    this->mock_data = mock_data;
}

int Hashtable::hash(int id){

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


void Hashtable::resize(){
    cout << "start resize " << endl;
    Index** hashtable_old = hashtable;
    int table_size_old = table_size;

    this->table_size = table_size*2;
    depth+=1;

    this->hashtable = new Index*[this->table_size];
    for (int i=0; i<this->table_size; i++)
        this->hashtable[i] = new Index();
    
    this->emptySpaces = this->table_size;    
    
    //re-entering the previous elements
    for (int i=0; i<table_size_old; i++){
        if (hashtable_old[i]->get_has_value())  add(hashtable_old[i]->get_value(), hashtable_old[i]->get_value());
    }

    for (int i=0; i<table_size_old; i++) delete hashtable_old[i];
    delete [] hashtable_old;   
}


bool Hashtable::checkHashtableFull(){
    return (emptySpaces == 0);
}

bool Hashtable::checkBitmapFull(int index){
    return hashtable[index]->is_bitmap_full();
}

void Hashtable::add(int key, int value){
    cout << "to be added " << value << endl;
    //TEMPORARILY REPLACE HASH FUNC WITH TEMP_FIND_HASH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (checkHashtableFull()) resize();    
    int hashed_key = temp_find_hash(key, mock_data);
    
    while (checkBitmapFull(hashed_key)) {
        resize();        
        hashed_key = temp_find_hash(key, mock_data);
    }
    while (!insert(hashed_key, value)){
        resize();        
        hashed_key = temp_find_hash(key, mock_data);
    }     
}

bool Hashtable::insert(int hashed_key, int value){
    int pos = findPos(hashed_key);
    if (pos == -1) return false;

    add_value(pos, value, hashed_key);
    emptySpaces--;
    return true;
}

int Hashtable::findPos(int hashed_key){
    int emptyPos = find_empty_index(hashed_key);
    return slideLeft(hashed_key, emptyPos);  
}

int Hashtable::slideLeft(int hashed_key, int emptyPos){
    while( ((emptyPos-hashed_key) % table_size) >= H ) {
        emptyPos = findSwapNeighbourPos(emptyPos);
        if (emptyPos == -1) return emptyPos;
    }
    return emptyPos;    
}

int Hashtable::swapEmpty(int emptyPos, int swapNeighborPos, int value, int hashed_key){
    add_value(emptyPos, value, hashed_key);
    remove_value(swapNeighborPos, value, hashed_key);
    emptyPos = swapNeighborPos;
    return emptyPos;
}

int Hashtable::checkBucketBitmap(int bucket, int& swapNeighborPos, bool& changed){
    int loop_counter=0;
    int pos = (bucket + table_size) % table_size;
    for (int p = 0; p < H; p++){ 
        if(hashtable[pos]->get_bitmap_index(loop_counter) == 1){
            changed = true;
            swapNeighborPos = (pos + p + table_size)%table_size;
            break;                        
        }
        loop_counter++;
    }
    return swapNeighborPos;
}

int Hashtable::findSwapNeighbourPos(int emptyPos){
    cout << "4" << endl;
    int swapNeighborPos=-1;
    // a) We find all H-1 positions that have values whose hash value k is in max H-1 distance from j
    int bucket;
    bool changed = false;
    //checking each neighboring bucket's bitmap to find y's original hash value (k)
    for (bucket = emptyPos - (H-1); bucket<emptyPos; bucket++){
        cout << "5" << endl;        
        swapNeighborPos=-1;
        swapNeighborPos = checkBucketBitmap(bucket, swapNeighborPos, changed);

        if (swapNeighborPos!=-1){    
            emptyPos = swapEmpty(emptyPos, swapNeighborPos, hashtable[swapNeighborPos]->get_value(), temp_find_hash(hashtable[swapNeighborPos]->get_value(), mock_data));
            break;  
        }
        else continue;
    }
    if (!changed) {
        cout << "No element y, table need rehashing!" << endl;
        return -1;
    }
    return emptyPos;
}

void Hashtable::Solve(){
    for (int counter=0; counter<11; counter++) {
        add(mock_data[counter][0], mock_data[counter][0]);
    }
}