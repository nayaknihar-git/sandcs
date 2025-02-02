#ifndef ARGPARSEUTILS_H
#define ARGPARSEUTILS_H
#include<bits/stdc++.h>
using namespace std;

void printHelp();
int  arg_parse(char* argv[], int argc, map<string, string> &options);
#endif // ARGPARSEUTILS_H
