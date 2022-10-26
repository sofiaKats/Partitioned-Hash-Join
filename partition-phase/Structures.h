#include <iostream>
#include <cstdint>

using namespace std;

typedef struct Tuple {
  int32_t key;
  int32_t payload;
} Tuple;

/**
* Type definition for a relation.
* It consists of an array of tuples and a size of the relation.
*/
typedef struct Relation {
  Tuple* tuples;
  uint32_t num_tuples;

  Relation(int size){
    tuples = new Tuple[size];
    num_tuples = size;
  }
} Relation;

typedef struct Hist{
  uint32_t length;
  int* arr;

  Hist(int size){
    arr = new int[size];
    length = size;
  }
} Hist;

typedef struct PrefixSum{
  uint32_t length;
  int** arr;

  PrefixSum(int size){
    arr = new int*[size];
    length = size;

    for (int i = 0; i < length; i++){
      arr[i] = new int[2];
    }
  }
} PrefixSum;

typedef struct Part{
  Relation* rel;
  PrefixSum* prefixSum;
} Part;
