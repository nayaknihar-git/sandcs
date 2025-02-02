#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
	cout << "Hello World" << endl;
	pid_t pid = syscall(SYS_getpid);
	int size = 64;
	void *array[1024];

	for (int i = 0; i < size; ++i) {
		array[i] = malloc(1000000);
		//std::cout << "allocating 1m : " << array[i] << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}


}
