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
} Relation;

/**
* Type definition for a relation.
* It consists of an array of tuples and a size of the relation.
*/
typedef struct Result {

} Result;

typedef struct Hist{
  uint32_t length;
  int* arr;
} Hist;

typedef struct PrefixSum{
  uint32_t length;
  int** arr;
} PrefixSum;
