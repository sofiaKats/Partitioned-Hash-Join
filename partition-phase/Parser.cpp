#include "Parser.h"

Relation* Parser::Parse(string fileName){
  ifstream file;
  string line;
  string val;
  Relation * rel;
  int i = 0, numLines = 0;

  file.open(fileName);

  if (!file.is_open()){
    cout << "Could not open file: " << fileName << endl;
    return NULL;
  }

  while (getline(file, line)){ //count lines to allocate relation table
    if (line.empty()) break;
    ++numLines;
  }
  file.clear();
  file.seekg(0);

  rel = new Relation(numLines);

  while(getline(file, line)){
    if (line.empty()) break;
    stringstream input_stringstream(line);
    getline(input_stringstream, val, '|');
    rel->tuples[i].key = i;
    rel->tuples[i++].payload = stol(val);
  }

  file.close();
  
  return rel;
}
