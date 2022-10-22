#include "Partition.h"
#include "math.h"

Partition::Partition(Relation* rel, int n){
  this->n = n;
  this->rel = rel;
  cout << "partition class"<<endl;
}

int Partition::Hash(int key, int n){
  uint32_t tmp = key << (32-n);
  return tmp >> (32-n);
}

PrefixSum* Partition::GetPrefixSum(){
  return prefixSum;
}

Relation* Partition::BuildPartitionedTable(){
  PrefixSum* prefixSum = CreatePrefixSum(CreateHistogram());
  Relation* partRel = new Relation();
  partRel->num_tuples = rel->num_tuples;
  partRel->tuples = new Tuple[partRel->num_tuples];

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
  Hist* hist = new Hist();
  int length = rel->num_tuples;
  int histLength = pow(2,n);

  hist->length = histLength;
  hist->arr = new int[histLength];

  //initialisation
  for (int i = 0; i < histLength; i++){
    hist->arr[i] = 0;
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

  this->prefixSum = prefixSum;
  return prefixSum;
}
