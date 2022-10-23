#include "Partition.h"


class PartitionedHashJoin {
private:
  int n; //for number of lsb for hashings
  int passesNum;
  Relation* relR;
  Relation* relS;
public:
  PartitionedHashJoin(Relation*, Relation*);
  Part* Solve();
  Part* PartitionRec(Part*);
  int Merge(Part*, Part*, int, int);
};
