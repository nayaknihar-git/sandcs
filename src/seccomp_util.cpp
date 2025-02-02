#include <bits/stdc++.h>
#include "seccomp_utils.h"
#include <seccomp.h>
#include <unistd.h>

using namespace std;

scmp_filter_ctx ctx = nullptr;

bool seccompInit()
{
	if(ctx)
		return true;
	cout << "seccompInit" << endl;
	ctx = seccomp_init(SCMP_ACT_ALLOW);
	if(ctx == nullptr)
	{
		perror("seccompInit failed");
		return false;
	}
	return true;
};

bool seccompAddRule(vector<string> &blocked_syscalls_list)
{
	bool status = true;
	if(!ctx)
	{
		std::cerr << "Context not Avail" << std::endl;
		return false;
	}

	cout << "secomp blocking systemcall : ";
	for (auto syscall_name: blocked_syscalls_list)
	{
		cout << syscall_name << " ";
		int syscall_num = seccomp_syscall_resolve_name(syscall_name.c_str());
		if (syscall_num == __NR_SCMP_ERROR)
		{
			std::cerr << "Unable to Get SysCall NUM" << std::endl;
			status = false;
			continue;
		}
		if (seccomp_rule_add(ctx, SCMP_ACT_ERRNO(EPERM), syscall_num, 0) < 0) 
		{
			std::cerr << "Failed add seccomp rule" << std::endl;
			status = false;
		}
	}
	cout << endl;
	return status;
};

void seccompExit()
{
	if(!ctx)
		return;
	seccomp_release(ctx);
	cout << "seccompExit" << endl;
};

