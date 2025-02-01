#include <bits/stdc++.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "cgroup_utils.h"
using namespace std;
const string mem_cgrpoup_path = "/sys/fs/cgroup/memory/";

bool cgroupMemAdd(string group_name)
{
	const string hellow_world_cg = mem_cgrpoup_path + group_name;
	if (mkdir(hellow_world_cg.c_str(), 0755) && errno != EEXIST)
	{
        	perror("mkdir : hellow_world_cg  create group failed");
	        return false;
	}
	cout << "cgroup " << hellow_world_cg << " created" << endl;
	return true;
} 

bool cgroupSetMemLimit(string group_name, string in_byte)
{
	const string memory_limit_file = mem_cgrpoup_path + group_name + "/memory.limit_in_bytes";

	int fd = open(memory_limit_file.c_str(), O_WRONLY);
 	if (fd == -1)
       	{
		perror("open failed to memory_limit_file");
	        return false;
	}
	if (write(fd, in_byte.c_str(), in_byte.length()) == -1)
	{
		perror("Unable to write memory limit");
		close(fd);
	        return false;
	}
	close(fd);
	cout << "cgroup mem limit " << memory_limit_file << " set to " << in_byte << " Bytes" <<  endl;
	return true;
}

bool cgroupMemAddPid(string group_name, string pid)
{
	const string task_pid_file = mem_cgrpoup_path + group_name + "/tasks";

	// Add current process to cgroup
	int fd = open(task_pid_file.c_str(), O_WRONLY);
	if (fd == -1)
	{
        	perror("unable to open task_pid_file");
	        return false;
	}
	if (write(fd, pid.c_str(), pid.length()) == -1)
	{
        	perror("Unable to write pid to cgroup");
		close(fd);
	        return false;
	}
	close(fd);
	cout << "cgroup " << group_name << " monitering pid : " << pid << endl;
	return true;
}

void cgroupMemRemove(string group_name)
{
	string command = "cgdelete -g memory:" + group_name;
	int res = system(command.c_str());
	if (res == -1)
	{
		cout << "Failed to Remove memory cgroup, Try Manually : groupname : " << group_name << endl;
	}
	cout << "cgroup " << group_name << " deleted" << endl;
}
