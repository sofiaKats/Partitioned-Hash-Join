#include "Structures.h"


class Partition {
private:
  int n; //for number of lsb for hashing
  int Hash(int32_t, int);
  PrefixSum* prefixSum;
  Relation* rel;

public:
  Partition(Relation*, int);
  Relation* BuildPartitionedTable();
  Hist* CreateHistogram();
  PrefixSum* CreatePrefixSum(Hist*);
  PrefixSum* GetPrefixSum();
};
