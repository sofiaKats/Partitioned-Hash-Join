#include <iostream>
#include <cstring>

#include "parser.h"

using namespace std;

//int main(){
int** readQueries(){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    const char s[2] = " ";

    fp = fopen("../hopscotch/src/Queries.tbl", "r");
    if (fp == NULL){
        cout << "File bad" << endl;
        exit(EXIT_FAILURE);
    }

    int numLines = 0;
    while ((read = getline(&line, &len, fp)) != -1) { //count lines to allocate relation table
        if (read == 0) break;
        ++numLines;
    }
    cout << "readQueries!\n";

    int** relIdsToJoin = new int*[numLines];
    numLines = 0;
    int i;
    rewind(fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        i = 0;

        relIdsToJoin[numLines] = new int[2];
        /* get the first token */
        token = strtok(line, s);
        
        /* walk through other tokens */
        while( token != NULL) {
            int ia = atoi(token);
            relIdsToJoin[numLines][i++] = ia;
            
            token = strtok(NULL, s);

        }
        cout << "ids are : " << relIdsToJoin[numLines][0] << relIdsToJoin[numLines][1] << endl;
        numLines++;
    }

   
    fclose(fp); 
    return relIdsToJoin;
}