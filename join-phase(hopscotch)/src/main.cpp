#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;

#include "hopscotch.h"

// execute program with ./hopscotch table_size
int main(int argc, char* argv[]) {

    if(argc > 1) {
        // fetching hashtable size from user for now (lets say 10)
        int table_size = atoi(argv[1]);

        srand(time(0));

        Index* hashtable[table_size];
        for (int i=0; i<table_size; i++)
            hashtable[i] = new Index();

        // creating mock data to test if the algorithm works.
        // mock_data column 0: holds a random value
        // mock_data column 1: holds hash value i create to test algorithm cases
        // lets assume that table_size=10
        int** mock_data = new int*[8];
        for(int i=0; i<8; i++) mock_data[i] = new int[2];
        //random value within [0,99] , pseudo-hash that i assign
        mock_data[0][0] = 14; mock_data[0][1] = 1;
        mock_data[1][0] = 67; mock_data[1][1] = 1;
        mock_data[2][0] = 5;  mock_data[2][1] = 1;
        mock_data[3][0] = 81; mock_data[3][1] = 3;
        mock_data[4][0] = 99; mock_data[4][1] = 5;
        mock_data[5][0] = 7;  mock_data[5][1] = 5;
        mock_data[6][0] = 23; mock_data[6][1] = 6;
        mock_data[7][0] = 55; mock_data[7][1] = 2;


        hopscotch_hatching(hashtable, mock_data, table_size);

        // free hashtable memory
        for (int i=0; i<table_size; i++) delete hashtable[i];
        //free mock data memory
        for(int i=0; i<8; i++) delete mock_data[i];
        delete [] mock_data;
    }

    return 0;
}