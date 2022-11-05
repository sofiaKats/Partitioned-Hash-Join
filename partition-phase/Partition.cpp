#include "Partition.h"

Partition::Partition(Relation* rel, int n, int from, int to){
  this->n = n;
  this->rel = rel;
  this->startIndex = from;
  this->endIndex = to == -1 ? rel->num_tuples : to;
}

int Partition::Hash(int key, int n){
  uint32_t tmp = key << (32 - n);
  return tmp >> (32 - n); 
}

Part* Partition::BuildPartitionedTable(){
  Part* parted = new Part();
  Hist* hist = CreateHistogram();

  parted->prefixSum = CreatePrefixSum(hist);
  parted->rel = new Relation(endIndex - startIndex);

  for (int i = startIndex; i < endIndex; i++){
    int hash = Hash(rel->tuples[i].payload, n);
    int index;

    for (int j = 0; j < parted->prefixSum->length; j++){
      if (parted->prefixSum->arr[j][0] == hash){
        index = parted->prefixSum->arr[j][1];
        break;
      }
    }

    for (; parted->rel->tuples[index].payload != 0; index++); //find empty bucket
    parted->rel->tuples[index] = rel->tuples[i];
  }

  delete hist;

  return parted;
}

Hist* Partition::CreateHistogram(){
  int histLength = pow(2,n);
  Hist* hist = new Hist(histLength);

  for (int i = startIndex; i < endIndex; i++){
    int index = Hash(rel->tuples[i].payload, n);
    hist->arr[index]++;
  }

  cout << "HISTOGRAM \n";
  for (int i = 0; i < histLength; i++){ //calculate largestTableSize
    if (hist->arr[i] == 0) continue;
    hist->usedLength++;
    if (hist->arr[i] > largestTableSize)
      largestTableSize = hist->arr[i];
    cout << i << " : " << hist->arr[i]<<endl;
  }

  return hist;
}

PrefixSum* Partition::CreatePrefixSum(Hist* hist){
  int psum = 0;
  int pIndex = 0;
  PrefixSum* prefixSum;

  prefixSum = new PrefixSum(hist->usedLength + 1);

  for (int i = 0; i < hist->length; i++){
    if (hist->arr[i] == 0)
      continue;

    prefixSum->arr[pIndex][0] = i;
    prefixSum->arr[pIndex++][1] = psum;
    psum += hist->arr[i];
  }
  prefixSum->arr[pIndex][0] = -1;
  prefixSum->arr[pIndex][1] = psum;

  cout << "PREFIX SUM" << endl;
  for (int i = 0; i < prefixSum->length; i++){
    cout << prefixSum->arr[i][0] << " : " << prefixSum->arr[i][1]<<endl;
  }

  return prefixSum;
}

uint32_t Partition::GetLargestTableSize(){
  return largestTableSize;
}
