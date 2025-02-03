#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main()
{
	cout << "Hello World" << endl;
	pid_t pid = syscall(SYS_getpid);

	const char* filename = "example.txt";
	int fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

	if (fd == -1) {
		std::cerr << "Failed to open file" << std::endl;
		return 1;
	}

	uid_t new_owner = 1001; // Replace with the desired user ID
	gid_t new_group = 1001; // Replace with the desired group ID

	cout << "Try to use fchown system call blocked by seccomp" << endl;
	if (fchown(fd, new_owner, new_group) == -1) {
		std::cerr << "Failed to change ownership" << std::endl;
		close(fd);
	}
	else {
 
    		std::cout << "Ownership changed successfully" << std::endl;
	        close(fd);
   	}

	cout << "allocate 1G of Memory  beyound memory limit" << endl;
	try {
		// Allocate a large amount of memory (e.g., 1 GB)
		size_t size = 1024 * 1024 * 1024; // 1 GB
		char* largeArray = new char[size];

		// Use the allocated memory
		for (size_t i = 0; i < size; ++i) {
		    largeArray[i] = 'a';
		}

		std::cout << "Memory allocated and initialized successfully." << std::endl;

		// Free the allocated memory
		delete[] largeArray;
	} catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed: " << e.what() << std::endl;
	}

	return 0;
}
