#include "PartitionedHashJoin.h"

#define L2CACHE 256000

PartitionedHashJoin::PartitionedHashJoin(Relation* relR, Relation* relS){
  this->relR = relR;
  this->relS = relS;
}

void PartitionedHashJoin::Solve(){
  Part* partitionedR = new Part();
  partitionedR->rel = new Relation(relR->num_tuples);
  int passCount = PartitionRec(partitionedR, relR);
  //ONLY FOR RELATION R
  BuildHashtables(partitionedR);

  Part* partitionedS = new Part();
  partitionedS->rel = new Relation(relS->num_tuples);
  PartitionRec(partitionedS, relS, passCount);

  //PrintPart(partitionedR, true);
  //PrintPart(partitionedS, false);

  Join(partitionedR, partitionedS);

  delete partitionedR;
  delete partitionedS;
}

 void PartitionedHashJoin::Merge(Part* destPart, Part* part, int from, int n){
   int partIndex = 0;
   int index = 0;
   int base = 0;

   //Merge Relation table
   for (int i = from; i < from + part->rel->num_tuples; i++){
     destPart->rel->tuples[i] = part->rel->tuples[partIndex++];
   }

   //Merge PrefixSum table
   if (destPart->prefixSum == NULL)
      destPart->prefixSum = new PrefixSum(pow(2, n) + 1);

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

int PartitionedHashJoin::PartitionRec(Part* finalPart, Relation* rel, int maxPasses, int n, int passNum, int from, int to){
  passNum++;
  n++;
  int passCount = 0;

  cout << "\n------- PASS NO: " << passNum << " -------\n\n";

  Partition* partition = new Partition(rel, n, from, to);

  Part* part = partition->BuildPartitionedTable();

  if (passNum == maxPasses || partition->GetLargestTableSize() < L2CACHE){
    //Merge Relation and PrefixSum table to finalPart tables
    Merge(finalPart, part, from, n);
    delete partition;
    delete part;
    return passNum;
  }

  for (int i = 0; i < part->prefixSum->length - 1; i++){
    from = part->prefixSum->arr[i][1];
    to = part->prefixSum->arr[i+1][1];

    passCount = PartitionRec(finalPart, part->rel, maxPasses, n, passNum, from, to);
  }

  delete partition;
  delete part;

  return passCount;
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
      //cout << "Payload is " << part->rel->tuples[indexR].payload << " and key is " << part->rel->tuples[indexR].key << endl;
      part->hashtables[i - 1]->add(part->rel->tuples[indexR].payload, part->rel->tuples[indexR].key);
      indexR++;
    }

    if(part->prefixSum->arr[i][0] == -1) break;  //  TO BE FIXED!!!!!!!!!!!
  }
}

// void PartitionedHashJoin::Join(Part* p1, Part* p2){
//   cout << "\n------- JOINING RELATIONS -------\n\n";
//   int hashtablesIndex = 0;

//   //For every partition table
//   for (int i = 0; i < p2->prefixSum->length; i++){
//     if (p2->prefixSum->arr[i][0] == -1) break;

//     int hash = p2->prefixSum->arr[i][0];
//     //cout << "P2 tuple with partition hash: " << hash << endl;

//     //if hash value exists in relation R
//     hashtablesIndex = ExistsInPrefix(hash, p1->prefixSum);

//     if (hashtablesIndex != -1){
//       //For every tuple in this partition
//       for (int j = p2->prefixSum->arr[i][1]; j < p2->prefixSum->arr[i+1][1]; j++){
//         //find hash value and neighborhood
//         int nei = p1->hashtables[hashtablesIndex]->GetH();
//         int payload2 = p2->rel->tuples[j].payload;
//         int hashhop = p1->hashtables[hashtablesIndex]->hash(payload2);

//         int currentBucket = hashhop;

//         for (int loops = 0; loops < nei ; loops++){
//           if (p1->hashtables[hashtablesIndex]->GetHashtable()[hashhop]->get_bitmap_index(loops) == 1){
//             int payload1 = p1->hashtables[hashtablesIndex]->GetHashtable()[currentBucket]->getTuple()->payload;

//             if (payload1 == payload2){
//               cout << "------- Match: " << payload2 << " RowId R: " << p1->hashtables[hashtablesIndex]->GetHashtable()[currentBucket]->getTuple()->key << " RowId S: " << p2->rel->tuples[j].key << " -------\n";
//             }
//           }
//           currentBucket = p1->hashtables[hashtablesIndex]->findNeighborPosByK(currentBucket, 1);
//         }
//       }
//     }
//     else cout << "------- No tuples in Relation R for partition hash " << hash << " -------" << endl;
//   }
// }
void PartitionedHashJoin::Join(Part* p1, Part* p2){
  cout << "\n------- JOINING RELATIONS -------\n\n";
  int hashtablesIndex = 0;

  //For every partition table
  for (int i = 0; i < p2->prefixSum->length; i++){
    if (p2->prefixSum->arr[i][0] == -1) break;

    int hash = p2->prefixSum->arr[i][0];
    //cout << "P2 tuple with partition hash: " << hash << endl;

    //if hash value exists in relation R
    hashtablesIndex = ExistsInPrefix(hash, p1->prefixSum);

    if (hashtablesIndex != -1){
      //For every tuple in this partition
      for (int j = p2->prefixSum->arr[i][1]; j < p2->prefixSum->arr[i+1][1]; j++){
        Tuple2* tuple2 = new Tuple2(p2->rel->tuples[j].key, p2->rel->tuples[j].payload);
        p1->hashtables[hashtablesIndex]->contains(tuple2);
        delete tuple2;
      }
    }
    //else cout << "------- No tuples in Relation R for partition hash " << hash << " -------" << endl;
  }
}

int PartitionedHashJoin::ExistsInPrefix(int hash, PrefixSum* prefixSum){
  for (int i = 0; i < prefixSum->length; i++){
    if (prefixSum->arr[i][0] == -1) return -1;
    if (prefixSum->arr[i][0] == hash){
      return i;
    }
  }
  return -1;
}

void PartitionedHashJoin::PrintHashtables(Part* part){
  for (int i = 1 ; i < part->prefixSum->length; i++){
    cout << "\n\nHASHTABLE NUMBER: " << i - 1 << endl;
    part->hashtables[i - 1]->print_hashtable();

    if(part->prefixSum->arr[i][0] == -1) break;
  }
}

void PartitionedHashJoin::PrintRelation(Relation* rel){
  cout << "\n----- Relation Table -----\n";
  for (int i = 0 ; i < rel->num_tuples; i++){
    cout << rel->tuples[i].payload << endl;
  }
}

void PartitionedHashJoin::PrintPrefix(PrefixSum* prefixSum){
  cout << "\n----- PrefixSum Table -----\n";
  for (int i = 0 ; i < prefixSum->length; i++){
    if (prefixSum->arr[i][0] == -1){
      cout << prefixSum->arr[i][0] << " : " << prefixSum->arr[i][1] << endl;
      break;
    }
    cout << prefixSum->arr[i][0] << " : " << prefixSum->arr[i][1] << endl;
  }
}

void PartitionedHashJoin::PrintPart(Part* part, bool hasHashtables){
  PrintRelation(part->rel);
  PrintPrefix(part->prefixSum);
  if (hasHashtables) PrintHashtables(part);
}
