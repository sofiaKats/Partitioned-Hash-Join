#include "PartitionedHashJoin.h"
#include "Parser.h"
#include "../hopscotch/src/parser.h"
#include <dirent.h>

using namespace std;

int main(int argc, char** argv){
  
  Parser* parser = new Parser();
  Relation *relR, *relS;
  Relation** relArray;
  
  if (argc < 3){
    cout << "[Main] Expected 2 arguments: " << argc - 1 << " provided\n";
  }

  DIR* FD;
  struct dirent* in_file;
  char* in_dir = argv[1];
  FILE* entry_file;
  int i = 0, numFiles = 0;

  if (NULL == (FD = opendir (in_dir))) 
  {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        return 1;
  }
  while ((in_file = readdir(FD))) 
  {
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))    
            continue;
        numFiles++;
  }
  relArray = new Relation*[numFiles];
  rewinddir(FD);
  while ((in_file = readdir(FD))) 
  {
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))    
            continue;
        char filePath[500];
        sprintf(filePath, "%s/%s", in_dir, in_file->d_name);
        relArray[i++] = parser->Parse(filePath);
  }
  closedir(FD);
  int** relIdsToJoin = readQueries();

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
