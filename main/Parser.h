#include <fstream>
#include <string>
#include <sstream>
#include "../partition-phase/Structures.h"
#include <dirent.h>

class Parser{
private:
  Relation* ParseRelation(string);

public:
  Relation** ReadRelations(char*, int&);
  int** ReadQueries(int&);
};
