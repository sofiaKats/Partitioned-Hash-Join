#include <iostream>
#include <cstdlib>
#include <cstring>
#include "math.h"
#include "Hashtable.h"
using namespace std;

// Hashtable::Hashtable(int table_size, int depth, int** mock_data){
//     this->emptySpaces = table_size;
//     this->table_size = table_size;
//     //this->table_size = findClosestPowerOf2(table_size);
//     //this->depth = findClosestPowerOf2(table_size);
//     this->depth = depth;

//     hashtable = new Index*[table_size];
//     for (int i=0; i<table_size; i++)
//         hashtable[i] = new Index();

//     this->mock_data = mock_data;
// }

Hashtable::Hashtable(int tableR_size){
    this->depth = findClosestPowerOf2(tableR_size);
    this->table_size = pow(2,depth);
    this->emptySpaces = table_size;
    if (table_size<32)  H = table_size;
    else                H = 32;                         //We choose 32 as stated in the origignal paper because it is an entire cache line

    hashtable = new Index*[table_size];
    for (int i=0; i<table_size; i++)
        hashtable[i] = new Index(H);

    //cout << "Hashtable size is " << table_size << endl;
}

Hashtable::~Hashtable(){
    for (int i = 0; i < table_size; i++){
        delete hashtable[i];
    }
    delete []hashtable;
}

int Hashtable::findClosestPowerOf2(int number){
    int counter = 0; 
    int power = 1;
    while(power < number){
        power*=2;
        counter++;
    }
    
    //cout << "Power is " << counter << endl;
    return counter;
}

int Hashtable::hash(int id){

    int i = 2;
    int j = 32;
    int hashed_value = (int) (id*2654435761 % (int)pow(i,j));

    hashed_value = hashed_value >> (31-depth);
    cout << "Hashed value is " << hashed_value << endl;
    return hashed_value;
}

void Hashtable::print_hashtable() {
    cout << "FINAL HASHTABLE: " << endl;
    for(int bucket=0; bucket<table_size; bucket++) {
        if (hashtable[bucket]->get_has_value()) cout << "   " << hashtable[bucket]->get_value();
        else cout << "   " << 0;
    }
    
    cout << endl << "\n Corresponding bitmaps: " << endl;
    for(int bucket = 0; bucket < table_size; bucket++) {
        cout << "BUCKET " << bucket << " with value:  ";
        if (hashtable[bucket]->get_has_value()) cout <<  hashtable[bucket]->get_value() << " : ";
        else                                    cout << "0: ";

        for (int bit=0; bit< H ; bit++)  cout << "  " << hashtable[bucket]->get_bitmap_index(bit);
        cout << endl;
    }
}

// HAVE TO CHANGE J AND K INITIAL VALUE, COULD BE -1 SOMETIMES
int Hashtable::find_empty_index(int i){
    int j=-1; // linear search of array for empty space
    for(int bucket=i; bucket<table_size; bucket++)
    {
        //cout << "2" << endl;
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
            //cout << "2" << endl;
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
    this->depth+=1;

    this->hashtable = new Index*[this->table_size];
    for (int i=0; i<this->table_size; i++)
        this->hashtable[i] = new Index(H);
    
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
    //cout << "to be added " << value << endl;

    if (checkHashtableFull()) resize();    
    int hashed_key = hash(key);
    
    while (checkBitmapFull(hashed_key)) {
        cout << "!!!!!!!!!!!!!!Resize2" << endl;
        resize();        
        hashed_key = hash(key);
    }
    while (!insert(hashed_key, value)){
        cout << "!!!!!!!!!!!!!!resize3" << endl;
        resize();        
        hashed_key = hash(key);
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
        //cout << "SlideLeft: emptyPos is " << emptyPos << " hashed key is " << hashed_key << endl;
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

int Hashtable::checkBucketBitmap(int bucket, int& swapNeighborPos, bool& changed, int loops){
    //cout << "We will do " << loops << " loops " << endl;
    //cout << "CheckBucketBitmap: bucket is " << bucket << endl;
    for (int bit_pos = 0; bit_pos < loops; bit_pos++){ 
        if(hashtable[bucket]->get_bitmap_index(bit_pos) == 1){
            changed = true;
            swapNeighborPos = findNeighborPosByK(bucket, bit_pos);
            break;                        
        }
    }
    return swapNeighborPos;
}

// int Hashtable::findSwapNeighbourPos(int emptyPos){
//     cout << "4" << endl;
//     int swapNeighborPos=-1;
//     // a) We find all H-1 positions that have values whose hash value k is in max H-1 distance from j
//     int bucket;
//     bool changed = false;
//     //checking each neighboring bucket's bitmap to find y's original hash value (k)
//     for (bucket = emptyPos - (H-1); bucket<emptyPos; bucket++){
//         cout << "5" << endl;        
//         swapNeighborPos = checkBucketBitmap(bucket, swapNeighborPos, changed, emptyPos - bucket -1);
//         cout << "findSwapNeighborPos: empty pos is " << swapNeighborPos << endl;

//         if (swapNeighborPos!=-1){    
//             emptyPos = swapEmpty(emptyPos, swapNeighborPos, hashtable[swapNeighborPos]->get_value(), hash(hashtable[swapNeighborPos]->get_value()));
//             cout << "findSwapNeighborPos: empty pos is " << emptyPos << endl;
//             break;  
//         }
//     }
//     cout << "Changed: " << changed << " npos: " << swapNeighborPos <<endl;
//     if (!changed) {
//         cout << "No element y, table need rehashing!" << endl;
//         return -1;
//     }
//     return emptyPos;
// }

int Hashtable::findSwapNeighbourPos(int emptyPos){
    //cout << "4" << endl;
    int swapNeighborPos=-1;
    int posLeftToCheckBitmaps = H-1;
    // a) We find all H-1 positions that have values whose hash value k is in max H-1 distance from j
    int bucket = emptyPos - (H-1);
    bool changed = false;
    //checking each neighboring bucket's bitmap to find y's original hash value (k)
    for (int i = 0; i< H - 1; i++){        
        
        //cout << "5" << endl;        
        swapNeighborPos = checkBucketBitmap(bucket, swapNeighborPos, changed, posLeftToCheckBitmaps);
        //cout << "findSwapNeighborPos: empty pos is " << swapNeighborPos << endl;

        if (swapNeighborPos!=-1){    
            emptyPos = swapEmpty(emptyPos, swapNeighborPos, hashtable[swapNeighborPos]->get_value(), hash(hashtable[swapNeighborPos]->get_value()));
            //cout << "findSwapNeighborPos: empty pos is " << emptyPos << endl;
            break;  
        }
        bucket = findNeighborPosByK(bucket, 1);
        posLeftToCheckBitmaps--;
    }
    //cout << "Changed: " << changed << " npos: " << swapNeighborPos <<endl;
    if (!changed) {
        cout << "No element y, table need rehashing!" << endl;
        return -1;
    }
    return emptyPos;
}

void Hashtable::Solve(int table_size){
    for (int counter=0; counter<table_size; counter++) {
        add(counter, counter);
    }
}

int Hashtable::findNeighborPosByK(int currPos, int k){
    return (currPos + k + table_size)%table_size;
}