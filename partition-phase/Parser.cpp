#include "Parser.h"

Relation* Parser::Parse(string fileName){
  ifstream file;
  file.open(fileName);
  if (!file.is_open()){
    cout << "Could not open file: " << fileName << endl;
    return NULL;
  }
  int i = 0, numLines = 0;
  Relation * rel;

  string line;
  string val;

  while (getline(file, line)){ //count lines to allocate relation table
    if (line.empty()) break;
    ++numLines;
  }
  file.clear();
  file.seekg(0);
  //count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
  rel = new Relation(numLines);
  /*int length = 600;
  rel = new Relation(length);
  for (int i = 0 ; i < length; i++){
    rel->tuples[i].key = i;
    rel->tuples[i].payload = i+1;
  }*/
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
