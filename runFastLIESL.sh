#!/bin/bash

g++ -Wall -o /media/jonas/geheim/Coding/LIESL/fastLIESLd/fastLIESL /media/jonas/geheim/Coding/LIESL/fastLIESLd/fastLIESL.cpp -lLIESL
echo "Input file: "$1
/media/jonas/geheim/Coding/LIESL/fastLIESLd/fastLIESL $1
if [ $? -ne 0 ]
then   
    echo "Evaluation aborted: exit code 1"
    exit
fi

pdflatex -interaction=nonstopmode $1.tex 1>/dev/null 2>&1
texfot --no-interactive --ignore invoking --ignore Version --ignore Overfull --ignore Underfull --ignore Warning  --ignore warning pdflatex -interaction=nonstopmode $1.tex

rmTexFiles 1>/dev/null 2>&1
#rm $1.tex
#echo $2
#if [ $2 -ne 0 ]
#then
#    rm $1.tex
#fi
     
echo "LIESL converged"
