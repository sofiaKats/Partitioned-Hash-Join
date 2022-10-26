#include "Partition.h"

Partition::Partition(Relation* rel, int n, int from, int to){
  this->n = n;
  if (to == -1) to = rel->num_tuples;

  this->rel = new Relation(to - from);

  for (int i = 0; i < this->rel->num_tuples; i++){
    this->rel->tuples[i] = rel->tuples[i + from];
  }
}

int Partition::Hash(int key, int n){
  uint32_t tmp = key << (32 - n);
  return tmp >> (32 - n);
}

PrefixSum* Partition::GetPrefixSum(){
  return prefixSum;
}

Relation* Partition::BuildPartitionedTable(){
  PrefixSum* prefixSum = CreatePrefixSum(CreateHistogram());
  Relation* partRel = new Relation(rel->num_tuples);

  for (int i = 0; i < rel->num_tuples; i++){
    int hash = Hash(rel->tuples[i].payload, n);
    int index;

    for (int j = 0; j < prefixSum->length; j++){
      if (prefixSum->arr[j][0] == hash){
        index = prefixSum->arr[j][1];
        break;
      }
    }

    for (; partRel->tuples[index].payload != 0; index++); //find empty bucket
    partRel->tuples[index].key = rel->tuples[i].key;
    partRel->tuples[index].payload = rel->tuples[i].payload;
  }
  return partRel;
}

Hist* Partition::CreateHistogram(){
  int histLength = pow(2,n);
  int length = rel->num_tuples;
  Hist* hist = new Hist(histLength);

  //initialisation
  for (int i = 0; i < histLength; i++){
    hist->arr[i] = 0;
  }

  for (int i = 0; i < length; i++){
    int index = Hash(rel->tuples[i].payload, n);
    hist->arr[index]++;
  }

  cout << "HISTOGRAM \n";
  for (int i = 0; i < histLength; i++){
    cout << i << " : " << hist->arr[i]<<endl;
  }

  return hist;
}

PrefixSum* Partition::CreatePrefixSum(Hist* hist){
  int psum = 0;
  int pIndex = 0;
  int counter = 0; //counting hist length(prefix length)
  PrefixSum* prefixSum;

  for (int i = 0; i < hist->length; i++){ //count hist length
    if (hist->arr[i] == 0)
      continue;
    counter++;
  }

  prefixSum = new PrefixSum(counter + 1);

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

  this->prefixSum = prefixSum;
  return prefixSum;
}

uint32_t Partition::GetLargestTableSize(){
  return 4;// to be fixed
}
