#include "PartitionedHashJoin.h"
#include "Parser.h"
#include "../hopscotch/src/parser.h"
#include <dirent.h>

using namespace std;

int main(int argc, char** argv){
  
  Parser* parser = new Parser();
  Relation *relR, *relS;
  
  
  if (argc < 3){
    cout << "[Main] Expected 2 arguments: " << argc - 1 << " provided\n";
  }

  Relation** relArray = parser->readRelations(argv[1]);
  int** relIdsToJoin = parser->readQueries();

  //return 0;
  relR = relArray[relIdsToJoin[0][0]];
  relS = relArray[relIdsToJoin[0][1]];

  PartitionedHashJoin* phj = new PartitionedHashJoin(relR, relS);
  Part* finalPart = phj->Solve();

  delete finalPart;
  delete parser;
  delete relR;
  //delete relS;
  delete phj;
}
