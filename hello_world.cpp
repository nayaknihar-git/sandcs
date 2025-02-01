#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/syscall.h>

using namespace std;

int main()
{
	cout << "Hello World" << endl;
	pid_t pid = syscall(SYS_getpid);
	std::cout << "The process ID is: " << pid << std::endl;
}
