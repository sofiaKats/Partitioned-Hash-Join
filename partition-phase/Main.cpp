#include "PartitionedHashJoin.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv){
  Parser* parser = new Parser();
  Relation *relR, *relS;

  if (argc < 3){
    cout << "[Main] Expected 2 arguments: " << argc-1 << " provided\n";
  }
  relR = parser->Parse(argv[1]);

  for (int i =0; i<relR->num_tuples; i++)
  {
    cout << "id: "<<relR->tuples[i].key<<" val: "<< relR->tuples[i].payload<<endl;
  }
  /*int length = 6;
  relR = new Relation(length);
  relS = new Relation(length);
  for (int i = 0 ; i < length; i++){
    relR->tuples[i].key = i;
    relS->tuples[i].key = i;
    relR->tuples[i].payload = i+1;
    relS->tuples[i].payload = i+2;
  }*/

  PartitionedHashJoin* phj = new PartitionedHashJoin(relR, relS);
  Part* finalPart = phj->Solve();

  cout << "\n----- Final Relation Table -----\n";
  for (int i = 0 ; i < finalPart->rel->num_tuples; i++){
    cout << finalPart->rel->tuples[i].payload << endl;
  }

  cout << "\n----- Final PrefixSum Table -----\n";
  for (int i = 0 ; i < finalPart->prefixSum->length; i++){
    cout << finalPart->prefixSum->arr[i][0] << " : " << finalPart->prefixSum->arr[i][1]<<endl;
  }
}
