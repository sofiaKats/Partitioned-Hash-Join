#include <iostream>
#include <cstring>

#include "parser.h"
#include <sstream>
#include <fstream>

using namespace std;

JoinQuery::JoinQuery(string query) {
    
}

int main(int argc, char** argv) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    const char s[2] = " ";

    fp = fopen("Queries.tbl", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        /* get the first token */
        token = strtok(line, s);
        
        /* walk through other tokens */
        while( token != NULL) {
            printf( "token: %s\n", token );
            int ia = atoi(token);
            char n2[10] = {0};   //initialize  array
            sprintf(n2, "%c%d.tbl", 'r', ia);
            cout << "n2 is " << n2 << endl;
            
            token = strtok(NULL, s);

        }
    }

   
    fclose(fp); 
    
    return 0;
}