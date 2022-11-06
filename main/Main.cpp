#include "../partition-phase/PartitionedHashJoin.h"
#include "Parser.h"
#include <dirent.h>

using namespace std;

int main(int argc, char** argv){

  Parser* parser = new Parser();
  Relation *relR, *relS;


  if (argc < 3){
    cout << "[Main] Expected 2 arguments: " << argc - 1 << " provided\n";
  }

  Relation** relArray = parser->readRelations(argv[1]);
  int relIdsCount = 0;
  int** relIdsToJoin = parser->readQueries(relIdsCount);

  for (int i = 0; i < relIdsCount; i++){
    cout << "---- Running Query no: " << i << " with relations - " << relIdsToJoin[i][0] << " : "<< relIdsToJoin[i][1] << endl;
    relR = relArray[relIdsToJoin[i][0]];
    relS = relArray[relIdsToJoin[i][1]];

    PartitionedHashJoin* phj = new PartitionedHashJoin(relR, relS);
    Part* finalPart = phj->Solve();

    delete finalPart;
    delete phj;
  }

  delete parser;
}
