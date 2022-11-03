#include "PartitionedHashJoin.h"

#define MAX_PASSES 2
#define MAX_PARTITIONS 5
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
    delete partition;
    delete part;
    return;
  }

  for (int i = 0; i < part->prefixSum->length - 1; i++){
    from = part->prefixSum->arr[i][1];
    to = part->prefixSum->arr[i+1][1];

    PartitionRec(finalPart, part->rel, n, passNum, from, to);
  }

  delete partition;
  delete part;
}

void PartitionedHashJoin::BuildHashtables(Part* part){
  int hashtablesLength = part->prefixSum->length;
  part->hashtables = new Hashtable*[hashtablesLength];
  int subRelationSize;
  int indexR = 0;
  //for every partition table
  for (int i = 1; i < hashtablesLength; i++){
    //find its size from prefix sum
    subRelationSize = part->prefixSum->arr[i][1] - part->prefixSum->arr[i - 1][1];

    //create new hashtable for this partition
    part->hashtables[i - 1] = new Hashtable(subRelationSize);

    //fill hashtable
    for (int j = 0; j < subRelationSize; j++){
      part->hashtables[i - 1]->add(part->rel->tuples[indexR].payload, part->rel->tuples[indexR].payload);
      indexR++;
    }

    if(part->prefixSum->arr[i][0] == -1) break;           //  TO BE FIXED!!!!!!!!!!!
  }
}

void PartitionedHashJoin::PrintHashtables(Part* part){
  for (int i = 1 ; i < part->prefixSum->length; i++){
    cout << "\n\nHASHTABLE NUMBER: " << i << endl; 
    part->hashtables[i - 1]->print_hashtable();

    if(part->prefixSum->arr[i][0] == -1) break;
  }
}