#include "PartitionedHashJoin.h"

#define MAX_PASSES 2

PartitionedHashJoin::PartitionedHashJoin(Relation* relR, Relation* relS){
  this->relR = relR;
  this->relS = relS;
}

Part* PartitionedHashJoin::Solve(){
  Part* part = new Part();
  Part* partitionedR = new Part();
  partitionedR->rel = new Relation(relR->num_tuples);
  partitionedR->prefixSum = new PrefixSum(pow(2,2) + 1);

  PartitionRec(partitionedR, relR);

  return partitionedR;
}

 void PartitionedHashJoin::Merge(Part* destPart, Part* part){
   int partIndex = 0;
   int index = 0;
   int base = 0;

   //Get starting indexes, to be changed...
   for (; destPart->rel->tuples[index].key != 0; index++);

   for (int i = index; i < index + part->rel->num_tuples; i++){
     destPart->rel->tuples[i] = part->rel->tuples[partIndex++];
   }

   for (index = 1; destPart->prefixSum->arr[index][1] != 0; index++);
   if (index == 1) index = 0; // if second element's start index is 0 then first is as well.
   else{
     index--;
     base = destPart->prefixSum->arr[index][1];
   }
   partIndex = 0;
   for (int i = index; i < index + part->prefixSum->length; i++){
     destPart->prefixSum->arr[i][0] = part->prefixSum->arr[partIndex][0];
     destPart->prefixSum->arr[i][1] = part->prefixSum->arr[partIndex++][1] + base;
   }
}

void PartitionedHashJoin::PartitionRec(Part* finalPart, Relation* rel, int passNum, int n){
  passNum++;
  n++;

  cout << "\n------- PASS NO: " << passNum << " -------\n\n";

  Partition* partition = new Partition(rel, n);

  Part* part = new Part();
  part->rel = partition->BuildPartitionedTable();
  part->prefixSum = partition->GetPrefixSum();

  if (passNum == MAX_PASSES){
    //Merge Relation and PrefixSum table to finalPart tables
    Merge(finalPart, part);
    return;
  }

  for (int i = 0; i < part->prefixSum->length - 1; i++){
    //Create table for each relation sub-table, to be changed...
    int length = part->prefixSum->arr[i+1][1] - part->prefixSum->arr[i][1];
    Relation* breakRel = new Relation(length);
    int startIndex = part->prefixSum->arr[i][1];

    for (int j = 0; j < length; j++){
      breakRel->tuples[j] = part->rel->tuples[j + startIndex];
    }

    PartitionRec(finalPart, breakRel, passNum, n);
  }
}
