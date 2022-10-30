#include "Structures.h"
#include <math.h>

class Partition {
private:
  int n; //for number of lsb for hashing
  int startIndex;
  int endIndex;
  int largestTableSize;
  Relation* rel;
  PrefixSum* prefixSum;
  int Hash(int32_t, int);

public:
  Partition(Relation*, int, int = 0, int = -1);
  Part* BuildPartitionedTable();
  Hist* CreateHistogram();
  PrefixSum* CreatePrefixSum(Hist*);
  PrefixSum* GetPrefixSum();
  uint32_t GetLargestTableSize();
};
