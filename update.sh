#!/bin/bash

#copy header to /usr/local/include
sudo cp LIESL.h /usr/local/include

#copy executable archive to /usr/local/lib
g++ -c LIESL.cpp
ar rvs libLIESL.a LIESL.o
sudo cp libLIESL.a /usr/local/lib

#delete trash
rm LIESL.o
rm libLIESL.a
