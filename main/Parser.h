#include <fstream>
#include <string>
#include <sstream>
#include "../partition-phase/Structures.h"
#include <dirent.h>

class Parser{
public:
  Relation** readRelations(char*);
  int** readQueries(int&);
  Relation* ParseRelation(string);
};
