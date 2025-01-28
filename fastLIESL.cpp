#include "LIESL.h"
#include <iostream>

int main(int argc, char* argv[]) {
  string title = "Platzhalter";
  bool showPics=true;
  int lang=0;
  string file = argv[1];
  string outputFile=argv[1];
  LIESL liesl(outputFile, title, showPics, lang);
  liesl.fastBuild(file);
}
