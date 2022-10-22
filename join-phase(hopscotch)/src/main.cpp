#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;


#define neighborhood_indexes 2 // this is the H value
#include "hopscotch.h"

// execute program with ./hopscotch table_size
int main(int argc, char* argv[]) {

    if(argc > 1) {
        // fetching hashtable size from user for now (lets say 7)
        int table_size = atoi(argv[1]);

        srand(time(0));

        Index* hashtable[table_size];
        for (int i=0; i<table_size; i++)
            hashtable[i] = new Index(0, neighborhood_indexes); //initializing array with values 0

        // creating mock data to test if the algorithm works.
        // mock_data column 0: holds a random value
        // mock_data column 1: holds hash value i create to test algorithm cases
        // lets assume that table_size=7
        int mock_data[table_size+2, 2]; //throwing 2 excess values to check what happens when the hashtable is full
        //random value within [0,99] , pseudo-hash i assign
        mock_data[0,0] = 67; mock_data[0,1] = 0;
        mock_data[1,0] = 5;  mock_data[1,1] = 2;
        mock_data[2,0] = 81; mock_data[2,1] = 6;
        mock_data[3,0] = 99; mock_data[3,1] = 2;
        mock_data[4,0] = 7;  mock_data[4,1] = 3;
        mock_data[5,0] = 23; mock_data[5,1] = 2;
        mock_data[6,0] = 55; mock_data[6,1] = 4;
        mock_data[7,0] = 12; mock_data[7,1] = 4;
        mock_data[8,0] = 45; mock_data[8,1] = 3;

        // free hashtable memory
        for (int i=0; i<table_size; i++) delete hashtable[i];
    }

    return 0;
}