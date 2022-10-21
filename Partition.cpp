#include "Partition.h"

int Partition::Hash(int key, int n){
  int32_t tmp = key << (32-n);
  return tmp >> (32-n);
}

Relation* Partition::BuildPartitionedTable(Relation* rel){
  CreatePrefixSum(CreateHistogram(rel));
  return null;
}

Hist* Partition::CreateHistogram(Relation* rel){
  Hist* hist = new Hist();
  int length = rel->num_tuples;
  int n = 1; //temporary
  int histLength = 2^n;

  hist->arr = new int[histLength];

  for (int i = 0; i < length; i++){
    int index = Hash(rel->tuples[i].payload, n);
    hist->arr[index]++;
  }
  for (int i = 0; i < length; i++){
    cout << i << " : " << hist->arr[i]<<endl;
  }

}
