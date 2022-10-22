//#include "PartitionedHashJoin.h"
#include "PartitionedHashJoin.h"

using namespace std;

int main(void){

  Relation* relR = new Relation();
  relR->num_tuples = 100;
  int length = relR->num_tuples;
  relR->tuples = new Tuple[length];

  for (int i = 0 ; i < length; i++){
    relR->tuples[i].key = i;
    relR->tuples[i].payload = i+1;
    //cout << relR->tuples[i].key<< endl;
  }

  PartitionedHashJoin* phj = new PartitionedHashJoin(relR, NULL);
  Relation* partRel = phj->Solve();

  for (int i = 0 ; i < partRel->num_tuples; i++){
    cout << partRel->tuples[i].payload << endl;
  }

//  PartitionedHashJoin* PHJ = new PartitionedHashJoin(relR, relS);
//  Result result = PHJ.Solve();
  //print
}
