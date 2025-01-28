#!/bin/bash

file="/media/jonas/geheim/Coding/LIESL/mainLIESL"

g++ -Wall -o $file $file.cpp -lLIESL
output=$($file 0 $1 | head -n1 | cut -d " " -f1)
$file 0 $1 # can optimize this (somehow include printing into previous cmd)

if [ $? -ne 0 ]
then   
    echo "Evaluation aborted: exit code 1"
    exit
fi

pdflatex -interaction=nonstopmode $output.tex 1>/dev/null 2>&1
makeglossaries $output 1>/dev/null 2>&1
pdflatex -interaction=nonstopmode $output.tex 1>/dev/null 2>&1
texfot --no-interactive --ignore invoking --ignore Version --ignore Overfull --ignore Underfull --ignore Warning  --ignore warning pdflatex -interaction=nonstopmode $output.tex
rmTexFiles 1>/dev/null 2>&1
rm $file
