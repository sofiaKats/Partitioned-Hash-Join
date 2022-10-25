#include <iostream>
#include <cstdlib>
#include <cstring>
#include "hopscotch.h"
using namespace std;

Index::Index() : has_value(false)
{
    bitmap = new int[H];
    // initializing bitmap with 0s
    for (int i=0; i<H; i++) bitmap[i] = 0;
}

Index::~Index()
{
    delete [] bitmap;
}

void Index::set_bitmap_index_to_1(const int index) { bitmap[index] = 1;}

void Index::set_bitmap_index_to_0(const int index) { bitmap[index] = 0; }

int Index::get_bitmap_index(const int index) { return bitmap[index]; }

bool Index::get_has_value(void) { return has_value; }

void Index::set_has_value(bool flag) { has_value = flag;}

void Index::set_value(const int val) { value = val; }

int  Index::get_value(void) { return value;}

void Index::print_bitmap(void) {
    for(int i=0; i<H; i++) cout << bitmap[i] ;
    cout << endl;
}

//returns true if full, false if not full
bool Index::is_bitmap_full(const int index) {
    for(int i=0; i<H; i++)
        if(bitmap[i] == 0) return false;
    return true;
}

