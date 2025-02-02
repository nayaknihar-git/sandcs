#ifndef SECCOMPUTILS_H
#define SECCOMPUTILS_H

#include<bits/stdc++.h>
using namespace std;

bool seccompInit();
bool  seccompAddRule(vector<string> &block_list);
void seccompExit();
#endif // SECCOMPUTILS_H
