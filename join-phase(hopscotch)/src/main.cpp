#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;

#include "Hashtable.h"

// execute program with ./hopscotch table_size
int main(int argc, char* argv[]) {

    if(argc > 1) {
        // fetching hashtable size from user for now (lets say 10)
        int table_size = atoi(argv[1]);

        srand(time(0));

        Hashtable* htable = new Hashtable(table_size, 10); //2^12 = 4096 * siexof(tuple) = 64 close to 256K = minimum (L2 CACHE)

        // creating mock data to test if the algorithm works.
        // mock_data column 0: holds a random value
        // mock_data column 1: holds hash value i create to test algorithm cases
        // lets assume that table_size=10
        int** mock_data = new int*[20];
        for(int i=0; i<20; i++) mock_data[i] = new int[2];
        //random value within [0,99] , pseudo-hash that i assign
        mock_data[0][0] = 14; mock_data[0][1] = 1;
        mock_data[1][0] = 67; mock_data[1][1] = 1;
        mock_data[2][0] = 5;  mock_data[2][1] = 1;
        mock_data[3][0] = 81; mock_data[3][1] = 3;
        mock_data[4][0] = 99; mock_data[4][1] = 5;
        mock_data[5][0] = 7;  mock_data[5][1] = 5;
        mock_data[6][0] = 23; mock_data[6][1] = 7;
        mock_data[7][0] = 55; mock_data[7][1] = 2;
        mock_data[8][0] = 16; mock_data[8][1] = 6;
        mock_data[9][0] = 46; mock_data[9][1] = 8;
        //mock_data[10][0] = 16; mock_data[10][1] = 6;
        //mock_data[11][0] = 17; mock_data[11][1] = 6;
        //mock_data[12][0] = 17; mock_data[11][1] = 9;


        //htable->hopscotch_hatching(mock_data);
        htable->Solve(mock_data);
        htable->print_hashtable();

        // free hashtable memory
        //for (int i=0; i<table_size; i++) delete hashtable[i];
        //free mock data memory
        for(int i=0; i<10; i++) delete mock_data[i];
        delete [] mock_data;
    }

    return 0;
}