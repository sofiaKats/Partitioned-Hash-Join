#include "PartitionedHashJoin.h"

#define MAX_PASSES 2
#define MAX_PARTITIONS 4
#define L2CACHE 1

PartitionedHashJoin::PartitionedHashJoin(Relation* relR, Relation* relS){
  this->relR = relR;
  this->relS = relS;
}

Part* PartitionedHashJoin::Solve(){
  Part* partitionedR = new Part();
  //Part* partitionedS = new Part();

  partitionedR->rel = new Relation(relR->num_tuples);
  partitionedR->prefixSum = new PrefixSum(pow(2, MAX_PARTITIONS) + 1);

  //partitionedS->rel = new Relation(relS->num_tuples);
  //partitionedS->prefixSum = new PrefixSum(pow(2,2) + 1);

  PartitionRec(partitionedR, relR, 2);
  //PartitionRec(partitionedS, relS);

  return partitionedR;
}

 void PartitionedHashJoin::Merge(Part* destPart, Part* part, int from){
   int partIndex = 0;
   int index = 0;
   int base = 0;

   //Merge Relation table
   for (int i = from; i < from + part->rel->num_tuples; i++){
     destPart->rel->tuples[i] = part->rel->tuples[partIndex++];
   }

   //Merge PrefixSum table
   for (index = 1; destPart->prefixSum->arr[index][1] != 0; index++);
   if (index == 1) index = 0; // if second element's start index is 0 then first is as well.
   else{ //get end position of previous prefix sum table to continue from
     index--;
     base = destPart->prefixSum->arr[index][1];
   }

   partIndex = 0;
   for (int i = index; i < index + part->prefixSum->length; i++){
     destPart->prefixSum->arr[i][0] = part->prefixSum->arr[partIndex][0];
     destPart->prefixSum->arr[i][1] = part->prefixSum->arr[partIndex++][1] + base;
   }
}

void PartitionedHashJoin::PartitionRec(Part* finalPart, Relation* rel, int n, int passNum, int from, int to){
  passNum++;
  n++;

  cout << "\n------- PASS NO: " << passNum << " -------\n\n";

  Partition* partition = new Partition(rel, n, from, to);

  Part* part = partition->BuildPartitionedTable();

  if (passNum == MAX_PASSES || partition->GetLargestTableSize() < L2CACHE){
    //Merge Relation and PrefixSum table to finalPart tables
    Merge(finalPart, part, from);
    return;
  }

  for (int i = 0; i < part->prefixSum->length - 1; i++){
    from = part->prefixSum->arr[i][1];
    to = part->prefixSum->arr[i+1][1];

    PartitionRec(finalPart, part->rel, n, passNum, from, to);
  }
}

PartitionedHashJoin::~PartitionedHashJoin(){
  
}
