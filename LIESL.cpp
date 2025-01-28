#include "LIESL.h"

LIESL::LIESL(string outputFile, string title, bool showPics, int lang) {
  this->outputFile=outputFile;
  this->title=title;
  this->showPics=showPics;
  this->lang=lang;
  vector<string> titles;
  vector<string> acronyms;
  output="";
  bool fastLIESL=false; //may be set to true later
}

void LIESL::writeFile() {
  if(showPics) outputFile=outputFile+".tex";
  else outputFile=outputFile=outputFile+"+.tex";
  cout << "Write to file " << outputFile << endl;
  output+="\\end{document} \n";
  ofstream out(outputFile);
  out << output;
  out.close();
}

void LIESL::head() {
  if(isReport) output+="\\documentclass[a4paper, 11pt]{report} \n";
  else output+="\\documentclass[a4paper, 11pt]{article} \n";
  output+="\\usepackage[T1]{fontenc} \n";
  output+="\\usepackage[utf8]{inputenc} \n";
  if(lang==0) output+="\\usepackage[ngerman]{babel} \n";
  else if(lang==1) output+="\\usepackage[english]{babel} \n";
  output+="\\usepackage[autostyle=false, english=british]{csquotes} \n";
  output+="\\usepackage{amsmath,amssymb,amsfonts,mathrsfs,bbm,bbold,siunitx,graphicx,float,geometry,slashed,caption,setspace,simplewick,xcolor, booktabs} \n";
  output+="\\usepackage[final, colorlinks, linkcolor=purple, citecolor=teal, urlcolor=blue]{hyperref} \n";
  output+="\\usepackage{tgpagella} \n";
  output+="\\usepackage[sfdefault]{FiraSans} \n";
  output+="%\\setcounter{secnumdepth}{0} \n";
  output+="\\usepackage[export]{adjustbox} \n";
  output+="\\geometry{a4paper, top=10mm, left=10mm, right=10mm, bottom=15mm} \n";
  output+="\\captionsetup{font={small,stretch=0}} \n";
  output+="\\parindent0cm \n\n";
  output+="\\newcommand{\\tr}{\\text{tr}} \n\n";
  output+="\\usepackage[nopostdot,nonumberlist]{glossaries} \n";
  output+="\\makeglossaries \n";
  output+="\\setacronymstyle{long-short} \n\n";
}

void LIESL::titlepage() {
  output+="\\title{"+title+"} \n";
  output+="\\author{Jonas Spinner} \n";
  output+="\\date{\\today} \n";
  output+="\\begin{document} \n";
  output+="\\maketitle \n";
}

void LIESL::titlepage(vector<string> literature, string abstractFile) {
  output+="\\begin{document} \n";
  output+="\\begin{titlepage} \n";
  output+="\\begin{center} \n";
  output+="\\vspace*{10cm} \n";
  output+="\\Huge\\textbf{"+title+"} \\\\ \n";
  output+="\\vspace{1cm} \n";
  output+="\\large Jonas Spinner \\\\ \n"; //hier Namen ändern
  output+="\\large \\today \\\\ \n";
  output+="\\vspace{1cm} \n";
  if(lang==0) {
    output+="Bitte nicht diese pdf weiterverbreiten, \\\\ \n";
    output+="sondern den Link \\url{https://www.jspinner.de}. \\\\\n";
    output+="Dort gibts die aktuelle Version!\n";
    output+="\\end{center} \n";
    output+="\\vspace{1cm} \n";
    output+="Dies ist eine privat erstellte Zusammenfassung und richtet sich an einen Studenten, der das Thema bereits aus einer Einführungsvorlesung kennt. Übersichtlichkeit und Struktur sind mir besonders wichtig, deshalb schreibe ich in Stichpunkten. Ich kommentiere die Themen, die ich wichtig finde und zeige die Rechnungen, die ich lehrreich finde. Insbesondere versuche ich, Aussagen zu verallgemeinern und direkt zu formulieren, was sicherlich manchmal schief geht. Ich freue mich über Rückmeldungen! \n \n";  //hier Text auf der Titelseite ändern
  } else if(lang==1) {
    output+="Please do not distribute this file, \\\\ \n";
    output+="but the link \\url{https://www.jspinner.de}. \\\\\n";
    output+="You can find the up-to-date version there.\n";
    output+="\\end{center} \n";
    //output+="\\vspace{1cm} \n";
    //output+="Dies ist eine privat erstellte Zusammenfassung und richtet sich an einen Studenten, der das Thema bereits aus einer Einführungsvorlesung kennt. Übersichtlichkeit und Struktur sind mir besonders wichtig, deshalb schreibe ich in Stichpunkten. Ich kommentiere die Themen, die ich wichtig finde und zeige die Rechnungen, die ich lehrreich finde. Insbesondere versuche ich, Aussagen zu verallgemeinern und direkt zu formulieren, was sicherlich manchmal schief geht. Ich freue mich über Rückmeldungen! \n \n";  //hier Text auf der Titelseite ändern    
  }
  if(!literature.empty()) {
    output+="\\vspace{0.5cm} \n";
    if(lang==0) output+="Im Folgenden eine kleine Liste von Quellen, auf die ich beim Anfertigen dieser Zusammenfassung zurückgegriffen habe. Die Punkte sind nach abnehmender Relevanz geordnet. \n";
    else output+="This is a brief summary of references that were helpful for me while learning the subject. They are ordered by relevance. \n";
    output+="\\begin{itemize} \n";
    for(int i=0; i<literature.size(); i++) {
      output+="\\item ";
      output+=literature[i]+" \n";
    }
    output+="\\end{itemize} \n";
  }
  output+="\\vfill \n";
  output+="\\end{titlepage} \n";
  if(!abstractFile.empty()) {
    if(lang==0) output+="\\section*{\\centering Überblick} \n";
    else output+="\\section*{\\centering Overview} \n";
    buildChapter(abstractFile);
    cout << "Abstract successfully built" << endl;
  }
  output+="\\newpage \n";
  output+="\\tableofcontents \n";
  output+="\\newpage \n";
}
  
void LIESL::loadGlossary(string glossaryFile) {
  output+="\\loadglsentries{"+glossaryFile+"} \n";
  
  ifstream in(glossaryFile);
  string input;
  char buffer;
  while(in.get(buffer)) input+=buffer;  //catch file not found error here 
  in.close();
  // fill acronyms array
  int i=0, j;
  string buff1, buff2, buff3;
  while(i<input.size()) {
    if(input.substr(i, 12)=="\\newacronym{") {
      i+=12;
      j=input.find('}', i);
      buff1=input.substr(i,j-i);
      if(input.substr(j,2)!="}{") {cout << "ERROR: Acronym file syntax error 1" << endl; exit(1);}
      i=j+2;
      j=input.find('}', i);
      buff2=input.substr(i,j-i);
      if(input.substr(j,2)!="}{") {cout << "ERROR: Acronym file syntax error 2" << endl; exit(1);}
      i=j+2;
      j=input.find('}', i);
      buff3=input.substr(i,j-i);
      i=j;

      if(buff1!=buff2) {cout << "ERROR: 1st and 2nd argument of newacronym do not match" << endl; exit(1);}
      acronyms.push_back(buff1);
    }
    i++;
  }
  cout << "Glossary successfully built" << endl;
}

void LIESL::lastPage() {
  output+="\\clearpage \n";
  output+="\\glsaddall \n";
  output+="\\printglossary[title=Abkürzungen] \n";
}
  
void LIESL::build(vector<string> files, vector<string> titles, vector<string> literature, string abstractFile, string glossaryFile) {
  fastLIESL=false;
  if(files.size()==0) {cout << "ERROR: No files available" << endl; exit(1);}
  else if(files.size()==1 && literature.size()==0) isReport=false; 
  else isReport=true;
  if(isReport && (files.size() != titles.size())) {cout << "ERROR: Length of files array and titles array does not match" << endl; exit(1);} //No need for chapter titles if isReport==False
  // start to create tex file
  head();
  if(!glossaryFile.empty()) loadGlossary(glossaryFile);
  if(literature.size()==0) titlepage();
  else titlepage(literature, abstractFile);
  for(int i=0; i<files.size(); i++) {
    if(isReport) buildChapter(files[i], titles[i]);
    else buildChapter(files[i]);
    cout << "Chapter " << files[i] << " successfully built" << endl;
  }
  if(!glossaryFile.empty()) lastPage();
  writeFile();
}

void LIESL::fastBuild(string file) {
  fastLIESL=true;
  isReport=false;
  head();
  output+="\\begin{document} \n";
  buildChapter(file+".txt");
  
  writeFile();
}

void LIESL::buildChapter(string file, string title) {
  output+="\\chapter{"+title+"} \n";
  buildChapter(file);
}

void LIESL::buildChapter(string file) {
  ifstream in(file);
  string input;
  char buffer;
  while(in.get(buffer)) input+=buffer;  //catch file not found error here 
  in.close();

  int i=0;  //main iteration index
  int i0=-1;  //save last iteration index to avoid infinite loop
  int j,l; //buffer index
  int level=0;  //current level in nested lists
  int nFigs; //number of figures in figure environment

  bool mathMode=false; //switch for math mode in latex
  bool quoteMode=false; //switch for quotation mode(with csquote's enquote)
  bool manualMode=false; //switch for manual mode(write plain code to file)
  bool tableMode=false; //switch to table mode
  vector<bool> isItemize; //information about list type(itemize vs itemize)

  const char fc=':';
  const char mc='_';
  //const char tc=';'; //Idee: führe für alle convention dinge Parameter ein, damit ich sie schnell ändern kann

  const string fs=string() + fc+fc; //string with twice fc (used to see figure mode)
  //const string ts=string() + tc+tc; //string with twice tc (used to see table mode)
  
  while(i<input.size()) { 
    if(i0==i) {cout << "ERROR: Infinite loop |_i=" << i << "_" << input.substr(i-10,20)<< endl; exit(1);}
    i0=i;
    
    if(input[i]==mc && input[i+1]==mc && input[i+2]==mc) {	//toggle manualMode with "___"
      manualMode=!manualMode;
      i+=3;
      continue;
    /*} else if(input[i]==tc && input[i+1]==tc) {  //toggle table mode
      cout << "BIN IM TABLE MODE" << endl;
      i+=2;
      if(!tableMode) {
	output+="\\begin{table}[tb] \n";
	output+="\\centering \n";
	j=input.find(ts, i);
	output+="\\caption{"+input.substr(i,j-i)+"} \n";
	i=j+2;
	j=input.find(ts, i);
	output+="\\begin{tabular}{"+input.substr(i, j-i)+"} \n";
	i=j+2;
      } else {
	output+="\\end{tabular} \n";
	output+="\\end{table} \n";
      }
      tableMode=!tableMode;*/
    } else if(input[i]==fc && input[i+1]==fc) { //enter figure mode
      if(!showPics) {i=input.find_first_of('\n',i); continue;} //directly leave, if no figures wanted
      i+=2;
      j=input.find(fs,i);
      nFigs=stoi(input.substr(i,j-i));
      output+="\\begin{figure}[tb] \n";
      for(l=0; l<nFigs; l++) {
	i=j+2;
	j=input.find(fs,i);
	output+="\\begin{minipage}{"+input.substr(i,j-i)+"\\linewidth} \n\\centering \n";
	i=j+2;
	j=input.find(fs,i);
	output+="\\includegraphics[scale="+input.substr(i,j-i);
	i=j+2;
	j=input.find(fs,i);
	output+="]{";
	if(!fastLIESL) output+="pics/";
	output+=input.substr(i,j-i)+"} \n";
	i=j+2;
	j=input.find(fs,i);
	output+="\\caption*{"+input.substr(i,j-i)+"} \n";
	output+="\\end{minipage} \n";
      }
      i=j+2;
      output+="\\end{figure} \n";
      if(input[i]!='\n') {cout << "ERROR: Figure environment does not end with '\\n' |_i=" << i << "_" << input.substr(i-10,20) << endl; exit(1);}
    } else if( (input[i]=='\n' && !manualMode) || i==0) { //hier evtl && !tableMode einfügen
      if(input[i]=='\n') {output+="\n";}
      if(mathMode==true) {
	output+="$";
	mathMode=false;
	cout << "WARNING: Missing $ |_i=" << i << "_" << input.substr(i-10,20) << endl; 
      }

      while(i+1 < input.size() && input[i]=='\n') i++; //skip empty lines
      
      if(i+1==input.size()) { //break if end of document is reached
	break;
      } else if(input[i]=='#' && input[i+1]=='#' && input[i+2]=='#') {	//Section begin
	if(i!=0 && input[i-1]!='\n') {cout << "ERROR: section beginning in mid line |_i=" << i << ",_" << input.substr(i-10,20) << endl; exit(1);} //throw exception here
	closeBrackets(level, isItemize);
	i=i+3;
	j=input.find_first_of('\n',i);
	
	output+="\\section{"+input.substr(i,j-i)+"}";
	i=j;
      } else if(input[i]=='-' || input[i+1]==')' || input[i]==' ') { //Enumerate or itemize
	int actlevel=0;
	do {
	  actlevel++;
	  if(actlevel==5) {cout << "ERROR: Too deeply nested(max 4 layers) |_i=" << i << "_" << input.substr(i-10,20) << endl; exit(1);}

	  if(input[i]=='-' || input[i+1]==')') { //do nothing, if no item starts here
	    if(level<actlevel) {  //open new nested list, if necessary
	      if(actlevel>level+1) {cout << "WARNING: Unnecessary deep nesting |_i=" << i << "_" << input.substr(i-10,20) << endl;}
	      if(input[i]=='-') {output+="\\begin{itemize}\n"; isItemize.push_back(true);}
	      if(input[i+1]==')') {output+="\\begin{enumerate}\n"; isItemize.push_back(false);}
	      level++;
	    }
	    while(level>actlevel) { //have opened lists left -> close the differing lists(may be multiple ones)
	      if(isItemize.back()) output+="\\end{itemize}\n";
	      else output+="\\end{enumerate}\n";
	      isItemize.pop_back();
	      level--;
	    }
	    //case level==actlevel und isItemize.back() und input[i] passen zusammen -> Muss nichts machen, schreibe nur ein \item
	    if(level==actlevel && !isItemize.back() && input[i]=='-') { //switch list type from enumerate to itemize
	      output+="\\end{enumerate}\n\\begin{itemize}\n";
	      isItemize.pop_back();
	      isItemize.push_back(true);
	    } else if(level==actlevel && isItemize.back() && input[i+1]==')') { //switch list type from itemize to enumerate
	      output+="\\end{itemize}\n\\begin{enumerate}\n";
	      isItemize.pop_back();
	      isItemize.push_back(false);
	    }
	    output+="\\item ";
	    if(input[i]=='-') i++; else i+=2;
	    break;
	  }
	  i++;
	} while(input[i]==' ' || input[i]=='-' || input[i+1]==')');
      } else if((input[i]=='_' && input[i+1]=='_' && input[i+2]=='_') || (input[i]==':' && input[i+1]==':')) {
	continue;
      } else {  //subsection
	closeBrackets(level, isItemize);
	j=input.find_first_of('\n',i);
	output+="\\subsection{"+input.substr(i,j-i)+"}";
	i=j;
      }
    } else if(input[i]=='$' ){ //&& input[i-1]!='\\') { //flip mathMode
      mathMode=!mathMode;
      output+='$';
      i++;
    } else if(input[i]=='\"') {
      quoteMode=!quoteMode;
      if(quoteMode) output+="\\enquote{";
      else output+="}";
      i++;
    } else if(!mathMode && !manualMode && ((input[i]=='-' && input[i+1]=='>') || (input[i-1]=='-' && input[i]=='>'))) { //shorthand for ->
      output+=" $\\Rightarrow$ ";
      if(input[i]=='-') i+=2;
      else i++;
    } else if(!mathMode && input[i]=='%') { //shorthand for %
      output+="\\%";
      i++;
    } else if(!mathMode && !manualMode && input[i]=='&') { //shorthand for &
      output+="\\&";
      i++;
    } else { //just print if nothing special happened
      // replace acronyms by \gls{acronym}
      bool skip=false;
      for(int l=0; l<acronyms.size(); l++) {
	if(input.substr(i,acronyms[l].size())==acronyms[l] && !mathMode) {
	  output+="\\gls{"+acronyms[l]+"}";
	  i+=acronyms[l].size();
	  skip=true;
	}
      }
      if(skip) continue;
      
      // otherwise just pring
      if(input[i]=='#' && !manualMode) {cout << "ERROR: '#' character in plain text |_i=" << i << "_" << input.substr(i-10,20) << endl; exit(1);}
      output+=input[i];
      i++;
    }
  }
  closeBrackets(level, isItemize);
}
  
void LIESL::closeBrackets(int &level, vector<bool> &isItemize) {
  while(level>0) {
    if(isItemize.back()) output+="\\end{itemize}\n";
    else output+="\\end{enumerate}\n";
    isItemize.pop_back();
    level--;
  }
}
