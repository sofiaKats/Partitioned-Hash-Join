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
  void BuildHashtables(Part*);
  void PrintHashtables(Part*);
  void PrintFinalRelation(Part*);
  void PrintFinalPrefix(Part*);
  void PrintPart(Part*);
  void Join(Part*, Part*);
};
