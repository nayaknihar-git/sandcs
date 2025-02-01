#ifndef CGROUPPUTILS_H
#define CGROUPUTILS_H

#include <bits/stdc++.h>
using namespace std;

bool cgroupMemAdd(string group_name);
bool cgroupSetMemLimit(string group_name, string in_byte);
bool cgroupMemAddPid(string group_name, string pid);
void cgroupMemRemove(string);

#endif // UTILS_H
