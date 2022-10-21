#include "Structures.h"

class Partition {
private:
  int Hash(int32_t, int);
  PrefixSum* CreatePrefixSum(Hist*);

public:
  Partition(Relation*);
  Relation* BuildPartitionedTable(Relation*);
  Hist* CreateHistogram(Relation*);

};
