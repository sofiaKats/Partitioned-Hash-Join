#include "PartitionedHashJoin.h"

using namespace std;

int main(void){

  int length = 60;
  Relation* relR = new Relation(length);
  Relation* relS = new Relation(length);

  for (int i = 0 ; i < length; i++){
    relR->tuples[i].key = i;
    relS->tuples[i].key = i;
    relR->tuples[i].payload = i+1;
    relS->tuples[i].payload = i+3;
  }

  //Partition* part = new Partition(relR, 1);
  //part->CreatePrefixSum(part->CreateHistogram());

  PartitionedHashJoin* phj = new PartitionedHashJoin(relR, relS);
  Part* partRel = phj->Solve();

  cout << "\n----- Final Relation Table -----\n";
  for (int i = 0 ; i < partRel->rel->num_tuples; i++){
    cout << partRel->rel->tuples[i].payload << endl;
  }

  cout << "\n----- Final PrefixSum Table -----\n";
  for (int i = 0 ; i < partRel->prefixSum->length; i++){
    cout << partRel->prefixSum->arr[i][0] << " : " << partRel->prefixSum->arr[i][1]<<endl;
  }
}
