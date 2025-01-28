#include "LIESL.h"
#include <iostream>

int main(int argc, char* argv[]) {
  string outputFile;
  string title;
  vector<string> files;
  vector<string> titles;
  vector<string> literature;
  string abstractFile;
  string glossaryFile;

  int lang=stoi(argv[1]);
  
  bool showPics=true;
  if(argc==3) {
    int val=stoi(argv[2]);
    if(val==0) showPics=true;
    if(val==1) showPics=false;
  }

  string infile;
  if(lang==0) infile="LIESL.config";
  else if(lang==1) infile="LIESL_EN.config";
  ifstream in(infile);
  string input;
  char buffer;
  while(in.get(buffer)) input+=buffer;
  in.close();

  int i=0, j=0;
  string buff;
  while(i<static_cast<int>(input.size())) { //get warning from index comparison - why???
    //cout << i << input.substr(i,10) << endl;
    if(input[i]=='#') i=input.find('\n', i)+1;
    else if(input.substr(i,7)=="OUTFILE") {
      i+=7+1;
      j=input.find('\n',i);
      outputFile=input.substr(i,j-i);
      i=j;
    } else if(input.substr(i,8)=="ABSTRACT") {
      i+=8+1;
      j=input.find('\n',i);
      abstractFile=input.substr(i,j-i);
      i=j;
    } else if(input.substr(i,8)=="GLOSSARY") {
      i+=8+1;
      j=input.find('\n',i);
      glossaryFile=input.substr(i,j-i);
      i=j;
    } else if(input.substr(i,5)=="TITLE") {
      i+=5+1;
      j=input.find('\n',i);
      title=input.substr(i,j-i);
      i=j;
    } else if(input.substr(i,7)=="INFILES") {
      i=input.find('\n',i)+1;
      while(true) {
	if(input[i]=='#') i=input.find('\n', i)+1;
	j=input.find('\n',i);
	buff=input.substr(i,j-i);
	if(buff.empty()) break;
	files.push_back(buff);
	i=j+1;
      }
    } else if(input.substr(i,9)=="SECTITLES") {
      i=input.find('\n',i)+1;
      while(true) {
	if(input[i]=='#') i=input.find('\n', i)+1;
	j=input.find('\n',i);
	buff=input.substr(i,j-i);
	if(buff.empty()) break;
        titles.push_back(buff);
	i=j+1;
      }
    } else if(input.substr(i,10)=="LITERATURE") {
      i=input.find('\n',i)+1;
      while(true) {
	if(input[i]=='#') i=input.find('\n', i)+1;
	j=input.find('\n',i);
	buff=input.substr(i,j-i);
	if(buff.empty()) break;
        literature.push_back(buff);
	i=j+1;
      }
    } else {
      i++;
    }
  }
  
  if(title.empty()) {cout << "ERROR: No title" << endl; exit(1);}
  if(outputFile.empty()) {cout << "ERROR: No output file" << endl; exit(1);}
  if(files.empty()) {cout << "ERROR: No input files" << endl; exit(1);}
  if(titles.empty()) {cout << "ERROR: No section titles" << endl; exit(1);}

  /*
  cout << "OUTFILE:_" << outputFile << "_" << endl;
  cout << "TITLE:_" << title << "_" << endl;
  cout << "ABSTRACT:_" << abstractFile << "_" << endl;
  cout << "GLOSSARY:_" << glossaryFile << "_" << endl;
  for(int i=0; i<static_cast<int>(files.size()); i++) cout << "INFILE:_" << files[i] << "_" << endl;
  for(int i=0; i<static_cast<int>(titles.size()); i++) cout << "SECTITLE:_" << titles[i] << "_" << endl;
  for(int i=0; i<static_cast<int>(literature.size()); i++) cout << "LITERATURE:_" << literature[i] << "_" << endl;
  */
  if(showPics) cout << outputFile << " (Output File)" << endl;
  else cout << outputFile << "+ (Output File)" << endl;
  
  LIESL liesl(outputFile, title, showPics, lang);
  liesl.build(files, titles, literature, abstractFile, glossaryFile);
}
