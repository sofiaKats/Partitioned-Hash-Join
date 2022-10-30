#include "Parser.h"

Relation* Parser::Parse(string fileName){
  ifstream ifile(fileName);
  //if (!ifile.is_open()){
  //  cout << "Could not open file: " << fileName << endl;
  //  return NULL;
  //}
  int i = 0, numLines = 0;
  Relation * rel;

  string line;
  string val;

  /*while (getline(file, line)){ //count lines to allocate relation table
    if (line.empty()) break;
    ++numLines;
  }
  ifile.clear();
  ifile.seekg(0);*/
  //count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
  //rel = new Relation(numLines);
  int length = 6;
  rel = new Relation(length);
  for (int i = 0 ; i < length; i++){
    rel->tuples[i].key = i;
    rel->tuples[i].payload = i+1;
  }
  /*while(getline(file, line)){
    if (line.empty()) break;
    stringstream input_stringstream(line);
    getline(input_stringstream, val, '|');
    rel->tuples[i].key = i;
    rel->tuples[i++].payload = stol(val);
  }*/

  //ifile.close();
  return rel;
}
