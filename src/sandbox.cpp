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
#include "arge_parse.h"
#include "sytem_call_list.h"
using namespace std;

int main(int argc, char* argv[])
{
	map<string, string> argmap;
	arg_parse(argv, argc, argmap);

	string bin_name = "./hello_world"; //default
	if (argmap.find("bin") != argmap.end())
		bin_name = argmap["bin"];

	string binary_arg = "";
	if (argmap.find("arg") != argmap.end())
		binary_arg = argmap["arg"];

	string cgroup_name = "helloWorld"; //default
	if (argmap.find("name") != argmap.end())
		cgroup_name = argmap["name"];

	string no_bytes = "10240000"; // 10.24 mb default
	if (argmap.find("memory") != argmap.end())
		no_bytes = argmap["memory"];
	
	cout << "Sandboxing ...: " << bin_name << " " << binary_arg << endl;

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		seccompInit();
		seccompAddRule(SANDBOX_SYSTEMCALLS);
		string cur_pid = to_string(getpid());
		if(!set_mem_limit(cgroup_name, no_bytes, cur_pid)) {
			perror("set_mem_limit Failed");
		}

		string command = bin_name + " " + binary_arg;
		int result = system(command.c_str());
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
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
		    cout << "Child exited with status: " << WEXITSTATUS(status) << endl;
		} else if (WIFSIGNALED(status)) {
		    cout << "Child killed by signal: " << WTERMSIG(status) << endl;
		} else if (WIFSTOPPED(status)) {
		    cout << "Child stopped by signal: " << WSTOPSIG(status) << endl;
		} else {
		    cout << "Child process status unknown" << endl;
		}
	}

	return 0;
}
