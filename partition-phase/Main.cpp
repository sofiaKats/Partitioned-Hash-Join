#include "PartitionedHashJoin.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv){
  Parser* parser = new Parser();
  Relation *relR, *relS;

  if (argc < 3){
    cout << "[Main] Expected 2 arguments: " << argc - 1 << " provided\n";
  }
  relR = parser->Parse(argv[1]);

  PartitionedHashJoin* phj = new PartitionedHashJoin(relR, relS);
  Part* finalPart = phj->Solve();

  cout << "\n----- Final Relation Table -----\n";
  for (int i = 0 ; i < finalPart->rel->num_tuples; i++){
    cout << finalPart->rel->tuples[i].payload << endl;
  }

  cout << "\n----- Final PrefixSum Table -----\n";
  for (int i = 0 ; i < finalPart->prefixSum->length; i++){
    if (finalPart->prefixSum->arr[i+1][1] == 0){
      cout << finalPart->prefixSum->arr[i][0] << " : " << finalPart->prefixSum->arr[i][1]<<endl;
      break;
    }
    cout << finalPart->prefixSum->arr[i][0] << " : " << finalPart->prefixSum->arr[i][1]<<endl;
  }

  delete finalPart;
  delete parser;
  delete relR;
  //delete relS;
  delete phj;
}
