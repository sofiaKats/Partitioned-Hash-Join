#include "Partition.h"


class PartitionedHashJoin {
private:
  Relation* relR;
  Relation* relS;
  void Merge(Part*, Part*, int);
  int ExistsInPrefix(int, PrefixSum*);

public:
  PartitionedHashJoin(Relation*, Relation*);
  void Solve();
  void PartitionRec(Part*, Relation*, int = 0, int = 0, int = 0, int = -1);
  void BuildHashtables(Part*);
  void Join(Part*, Part*);
  void PrintHashtables(Part*);
  void PrintRelation(Relation*);
  void PrintPrefix(PrefixSum*);
  void PrintPart(Part*, bool = false);
};
