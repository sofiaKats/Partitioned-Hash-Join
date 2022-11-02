#include <iostream>
#include <cstring>

#include "parser.h"

using namespace std;

JoinQuery::JoinQuery(string query) {
    
}

int main(int argc, char** argv) {
    char str[100]; // declare the size of string  
    strcpy(str, "0 2 4|0.1=1.2&1.0=2.1&0.1>3000|0.0 1.1");
    cout << "str is: "<< str << endl;    
    // cout << " Enter a string: " <<endl;  
    // cin.getline(str, 100); // use getline() function to read a string from input stream  
      
    char *ptr; // declare a ptr pointer  
    ptr = strtok(str, "|"); // use strtok() function to separate string using comma (,) delimiter.  
    cout << " \n Split string using strtok() function: " << endl;  
    // use while loop to check ptr is not null  
    while (ptr != NULL)  
    {  
        cout << ptr  << endl; // print the string token  
        ptr = strtok (NULL, "|");  
    } 
    
    cout << ptr << endl;
    return 0;
}