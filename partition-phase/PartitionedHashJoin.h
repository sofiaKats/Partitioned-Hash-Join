#include "Partition.h"

#define MAX_PASSES 2
#define N 0

class PartitionedHashJoin {
private:
  Relation* relR;
  Relation* relS;
  void Merge(Part*, Part*, int, int);
  int ExistsInPrefix(int, PrefixSum*);

public:
  PartitionedHashJoin(Relation*, Relation*);
  void Solve();
  int PartitionRec(Part*, Relation*, int = MAX_PASSES, int = N, int = 0, int = 0, int = -1);
  void BuildHashtables(Part*);
  void Join(Part*, Part*);
  void PrintHashtables(Part*);
  void PrintRelation(Relation*);
  void PrintPrefix(PrefixSum*);
  void PrintPart(Part*, bool = false);
};
