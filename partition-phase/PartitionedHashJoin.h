#include "Partition.h"


class PartitionedHashJoin {
private:
  int n; //for number of lsb for hashings
  Relation* relR;
  Relation* relS;
public:
  PartitionedHashJoin(Relation*, Relation*);
  Relation* Solve();
};
