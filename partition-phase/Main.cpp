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
  relS = parser->Parse(argv[2]);

  PartitionedHashJoin* phj = new PartitionedHashJoin(relR, relS);
  Part* finalPart = phj->Solve();

  //phj->BuildHashtables(finalPart);
  //phj->PrintHashtables(finalPart);

  delete finalPart;
  delete parser;
  delete relR;
  //delete relS;
  delete phj;
}
