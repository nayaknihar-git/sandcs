#include<bits/stdc++.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <string>


#include "seccomp_utils.h"
#include "cgroup_utils.h"
using namespace std;

int main()
{
	cout << "Helo Sandbox" << endl;
	string bin_name = "./hello_world";
	string cgroup_name = "helloWorld";
	string no_byte = "102400";
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		seccompInit();
		string cur_pid = to_string(getpid());
		cgroupMemAdd(cgroup_name);
		cgroupSetMemLimit(cgroup_name, no_byte);
		cgroupMemAddPid(cgroup_name, cur_pid);

		int result = system(bin_name.c_str());
		if (result == -1)
		{
			std::cerr << "Failed to execute the binary" << std::endl;
			seccompExit();
			cgroupMemRemove(cgroup_name);
			exit(EXIT_FAILURE);
		}

		seccompExit();
		cgroupMemRemove(cgroup_name);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}

	return 0;
}
