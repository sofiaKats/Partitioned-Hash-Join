#include "PartitionedHashJoin.h"

PartitionedHashJoin::PartitionedHashJoin(Relation* relR, Relation* relS){
  this->relR = relR;
  this->relS = relS;
  n = 1;
}

Relation* PartitionedHashJoin::Solve(){
  Partition* partitionR = new Partition(relR, n);
  //Partition* partitionS = new Partition(relS, n)

  Relation* partitionedRelR = partitionR->BuildPartitionedTable();
  PrefixSum* prefixSum = partitionR->GetPrefixSum();

  for (int i = 0; int < prefixSum.length){

  }
  
  return partitionedRelR;
}
