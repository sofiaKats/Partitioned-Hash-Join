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
  Part* partitionedRelR = PartitionRec(part);
  //Relation* partitionedRelS = PartitionRec(relS);

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

Part* PartitionedHashJoin::PartitionRec(Part* part){
  if (passesNum >= 2) {
    return part;
  }
  n++;
  passesNum++;
  int startPsIndex = 0;
  Part** partArr;
  Part* finalPart = new Part();
  cout << "\n------- PASS NO: " << n << " -------\n\n";

  Partition* partitionR = new Partition(part->rel, n);

  Relation* partitionedRelR = partitionR->BuildPartitionedTable();
  PrefixSum* prefixSum = partitionR->GetPrefixSum();
  partArr = new Part*[prefixSum->length-1];

  for (int i = 0; i < prefixSum->length - 1; i++){
    //cout << "PREFIX ARRAY VALUE : " << prefixSum->arr[i+1][1] - prefixSum->arr[i][1] << endl;

    Part* breakPart = new Part();
    breakPart->rel = new Relation();
    int length = prefixSum->arr[i+1][1] - prefixSum->arr[i][1];
    breakPart->rel->tuples = new Tuple[length];
    breakPart->rel->num_tuples = length;

    for (int j = 0; j < length; j++){
      breakPart->rel->tuples[j] = part->rel->tuples[j];
    }

    partArr[i] = PartitionRec(breakPart);

    //startPsIndex = Merge(finalPart, partArr[i], startIndex, startPsIndex);
  }
  return finalPart;
}
