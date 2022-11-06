#include <fstream>
#include <string>
#include <sstream>
#include "Structures.h"
#include <dirent.h>

class Parser{
public:
  Relation** readRelations(char*);
  int** readQueries();
  Relation* ParseRelation(string);
};
