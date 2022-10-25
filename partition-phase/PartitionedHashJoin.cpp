#include "PartitionedHashJoin.h"

#define MAX_PASSES 2

PartitionedHashJoin::PartitionedHashJoin(Relation* relR, Relation* relS){
  this->relR = relR;
  this->relS = relS;
}

Part* PartitionedHashJoin::Solve(){
  Part* part = new Part();
  Part* partitionedR = new Part();
  partitionedR->rel = new Relation();
  partitionedR->rel->tuples = new Tuple[relR->num_tuples];
  partitionedR->rel->num_tuples = relR->num_tuples;

  PartitionRec(partitionedR, relR);

  return partitionedR;
}

 void PartitionedHashJoin::Merge(Part* destPart, Part* part){
   int partIndex = 0;
   int relIndex = 0;
   int pSIndex = 0;

   //Get starting indexes, to be changed...
   for (; destPart->rel->tuples[relIndex].key != 0; relIndex++);

   //for (; part->prefixSum->arr[pSIndex][0] != 0; pSIndex++);

   cout << "Relation Index: " << relIndex << endl;
   cout << "pSum Index: " << pSIndex << endl;

   for (int i = relIndex; i < relIndex + part->rel->num_tuples; i++){
     destPart->rel->tuples[i] = part->rel->tuples[partIndex++];
   }

   /*partIndex = 0;
   for (int i = pSIndex; i < part->prefixSum->length; i++){
     destPart->prefixSum[i] = part->prefixSum[partIndex++];
   }*/
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
    Relation* breakRel = new Relation();
    int length = part->prefixSum->arr[i+1][1] - part->prefixSum->arr[i][1];
    int startIndex = part->prefixSum->arr[i][1];
    breakRel->tuples = new Tuple[length];
    breakRel->num_tuples = length;

    for (int j = 0; j < length; j++){
      breakRel->tuples[j] = part->rel->tuples[j + startIndex];
    }

    PartitionRec(finalPart, breakRel, passNum, n);
  }
}
