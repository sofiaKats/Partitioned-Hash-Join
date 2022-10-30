#include "Partition.h"


class PartitionedHashJoin {
private:
  Relation* relR;
  Relation* relS;
public:
  PartitionedHashJoin(Relation*, Relation*);
  Part* Solve();
  void PartitionRec(Part*, Relation*, int = 0, int = 0, int = 0, int = -1);
  void Merge(Part*, Part*, int);
  ~PartitionedHashJoin();
};
