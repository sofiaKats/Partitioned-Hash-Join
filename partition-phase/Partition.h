#include "Structures.h"


class Partition {
private:
  int Hash(int32_t, int);

public:
  Partition(Relation*);
  Relation* BuildPartitionedTable(Relation*);
  Hist* CreateHistogram(Relation*);
  PrefixSum* CreatePrefixSum(Hist*);
  
};
