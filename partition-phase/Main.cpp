#include "PartitionedHashJoin.h"

using namespace std;

int main(void){

  Relation* relR = new Relation();
  relR->num_tuples = 6;
  int length = relR->num_tuples;
  relR->tuples = new Tuple[length];

  for (int i = 0 ; i < length; i++){
    relR->tuples[i].key = i;
    relR->tuples[i].payload = i+1;
    //cout << relR->tuples[i].key<< endl;
  }

  //Partition* part = new Partition(relR, 1);
  //part->CreatePrefixSum(part->CreateHistogram());


  PartitionedHashJoin* phj = new PartitionedHashJoin(relR, NULL);
  Part* partRel = phj->Solve();

  /*for (int i = 0 ; i < partRel->rel->num_tuples; i++){
    cout << partRel->rel->tuples[i].payload << endl;
  }*/
}
