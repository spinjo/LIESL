#ifndef LIESL_H
#define LIESL_H

#include <iostream>
#include <vector> 
#include <fstream>
#include <iomanip>
using namespace std;

class LIESL {

public:
  LIESL();
  LIESL(string outputFile, string title, bool showPics, int lang);
  void build(vector<string> files, vector<string> titles, vector<string> literature, string abstractFile, string glossaryFile);
  void fastBuild(string file);
  
private:
  bool fastLIESL;
  string outputFile;
  string title;
  string output;
  bool isReport;
  bool showPics;
  int lang; //DE-0, EN-1
  vector<string> titles;
  vector<string> acronyms;
  void head();
  void titlepage();
  void titlepage(vector<string> literature, string abstractFile);
  void lastPage();
  void buildChapter(string file);
  void buildChapter(string file, string title);
  void closeBrackets(int &level, vector<bool> &isItem);
  void writeFile();
  void loadGlossary(string glossaryFile);
};

#endif
