#include "PartitionedHashJoin.h"

PartitionedHashJoin::PartitionedHashJoin(Relation* relR, Relation* relS){
  this->relR = relR;
  this->relS = relS;
  n = 0;
  passesNum = 0;
}

Part* PartitionedHashJoin::Solve(){
  Part* part = new Part();
  part->rel = relR;
  Part* partitionedRelR = PartitionRec(part, 0);
  //Relation* partitionedRelR = PartitionRec(relS);

  return partitionedRelR;
}

 int PartitionedHashJoin::Merge(Part* destPart, Part* part, int startIndex, int startPsIndex){
   int partIndex = 0;
   for (int i = startIndex; i < part->rel->num_tuples; i++){
     destPart->rel[i] = part->rel[partIndex++];
   }

   partIndex = 0;
   for (int i = startPsIndex; i < part->prefixSum->length; i++){
     destPart->prefixSum[i] = part->prefixSum[partIndex++];
   }

   return startPsIndex;
}

Part* PartitionedHashJoin::PartitionRec(Part* part, int startIndex, int num_tuples){
  if (passesNum >= 2) {
    return NULL;
  }
  n++;
  passesNum++;
  int startPsIndex = 0;
  Part** partArr;
  Part* finalPart = new Part();



  Partition* partitionR = new Partition(part->rel, n, startIndex, num_tuples);

  Relation* partitionedRelR = partitionR->BuildPartitionedTable();
  PrefixSum* prefixSum = partitionR->GetPrefixSum();
  partArr = new Part*[prefixSum->length-1];

  for (int i = 0; i < prefixSum->length - 1; i++){

    cout << "for no: " << i << endl;
    partArr[i] = PartitionRec(part, prefixSum->arr[i][1], prefixSum->arr[i][1], prefixSum->arr[i+1][1] - prefixSum->arr[i][1]);
    //startPsIndex = Merge(finalPart, partArr[i], startIndex, startPsIndex);
  }
  return finalPart;
}
