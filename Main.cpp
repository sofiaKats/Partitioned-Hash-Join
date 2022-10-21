//#include "PartitionedHashJoin.h"
#include "Partition.h"

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

  Partition* part = new Partition(relR);
  part->CreatePrefixSum(part->CreateHistogram(relR));

//  PartitionedHashJoin* PHJ = new PartitionedHashJoin(relR, relS);
//  Result result = PHJ.Solve();
  //print
}
