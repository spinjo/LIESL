### LImited Escape from Suffering in Latex (LIESL)

This is a C++ code that turns .txt files into .tex files, designed for summarizing learning materials during my bachelor and master studies (2019-2022), see https://spinjo.github.io/zsf. I am writing this in 2025, 3 years after having stopped using this tool in 2022. Everything is in german, and please don't ask why I didn't use markdown instead.

There is a grown-up version `runLIESL.sh` using `.config` files, this is how to install it on linux
1) Move LIESL.h to `/usr/local/include`
2) Link with `g++ -c LIESL.cpp` and `ar rvs libLIESL.a LIESL.o`
3) Move libLIESL.a to `/usr/local/lib`
4) Compile from anywhere using `g++ -o main main.cpp -lLIESL`

And there is a small version `runFastLIESL.sh` that simply takes `.txt` file as input.
