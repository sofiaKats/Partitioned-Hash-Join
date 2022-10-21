#include "Partition.h"
#include "math.h"

Partition::Partition(Relation* rel){
  cout << "partition class"<<endl;
}

int Partition::Hash(int key, int n){
  uint32_t tmp = key << (32-n);
  return tmp >> (32-n);
}

Relation* Partition::BuildPartitionedTable(Relation* rel){
  //CreatePrefixSum(CreateHistogram(rel));
  return NULL;
}

Hist* Partition::CreateHistogram(Relation* rel){
  Hist* hist = new Hist();
  int length = rel->num_tuples;
  int n = 1; //temporary
  int histLength = pow(2,n);

  hist->length = histLength;
  hist->arr = new int[histLength];

  //initialisation
  for (int i = 0; i < length; i++){
    hist->arr[i]=0;
  }

  for (int i = 0; i < length; i++){
    int index = Hash(rel->tuples[i].payload, n);
    hist->arr[index]++;
  }

  for (int i = 0; i < histLength; i++){
    cout << i << " : " << hist->arr[i]<<endl;
  }

  return hist;
}

PrefixSum* Partition::CreatePrefixSum(Hist* hist){
  int psum = 0;
  int pIndex = 0;
  int counter = 0; //counting hist length(prefix length)
  PrefixSum* prefixSum = new PrefixSum();

  for (int i = 0; i < hist->length; i++){ //count hist length
    if (hist->arr[i] == 0) continue;
    else counter++;
  }
  prefixSum->length = counter+1;
  prefixSum->arr = new int*[prefixSum->length];

  for (int i = 0; i < prefixSum->length; i++){
    prefixSum->arr[i] = new int[2];
  }

  for (int i = 0; i < hist->length; i++){
    if (hist->arr[i] == 0) continue;

    prefixSum->arr[pIndex][0] = i;
    prefixSum->arr[pIndex][1] = psum;
    pIndex++;
    psum += hist->arr[i];
  }
  prefixSum->arr[pIndex][0] = -1;
  prefixSum->arr[pIndex][1] = psum;

  cout <<"PREFIX SUM"<<endl;
  for (int i = 0; i < prefixSum->length; i++){
    cout << prefixSum->arr[i][0] << " : " << prefixSum->arr[i][1]<<endl;
  }

  return prefixSum;
}
