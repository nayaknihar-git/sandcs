#include <bits/stdc++.h>
#include "seccomp_utils.h"
#include <seccomp.h>
#include <unistd.h>

using namespace std;

scmp_filter_ctx ctx = nullptr;
vector<string> blocked_syscalls_list = { "acct",
        "add_key",
        "bpf",
        "chown",
        "clock_adjtime",
        "clock_settime",
        "create_module",
        "delete_module",
        "fchown",
        "fchownat",
        "finit_module",
        "get_kernel_syms",
        "get_mempolicy",
        "init_module",
        "ioperm",
        "iopl",
        "kcmp",
        "kexec_file_load",
        "kexec_load",
        "keyctl",
        "lchown",
        "lookup_dcookie",
        "mbind",
        "mount",
        "move_pages",
        "name_to_handle_at",
        "nfsservctl",
        "open_by_handle_at",
        "perf_event_open",
        "personality",
        "pivot_root",
        "process_vm_readv",
        "process_vm_writev",
        "ptrace",
        "query_module",
        "quotactl",
        "reboot",
        "request_key",
        "set_mempolicy",
        "setgid",
        "setns",
        "setregid",
        "setreuid",
        "settimeofday",
        "setuid",
        "stime",
        "swapon",
        "swapoff",
        "_sysctl",
        "umount",
        "umount2",
        "unshare",
        "uselib",
        "userfaultfd",
        "vm86",
        "vm86old",
    };

void seccompInit()
{
	if(ctx)
		return;
	cout << "seccompInit" << endl;
	ctx = seccomp_init(SCMP_ACT_ALLOW);
	if(ctx == nullptr)
	{
		perror("seccompInit failed");
	}
};

void seccompAddRule()
{
	if(!ctx)
	{
		std::cerr << "Context not Avail" << std::endl;
	}

	for (auto syscall_name: blocked_syscalls_list)
	{
		int syscall_num = seccomp_syscall_resolve_name(syscall_name.c_str());
		if (syscall_num == __NR_SCMP_ERROR)
		{
			std::cerr << "Unable to Get SysCall NUM" << std::endl;
			continue;
		}
		if (seccomp_rule_add(ctx, SCMP_ACT_ERRNO(EPERM), syscall_num, 0) < 0) 
		{
			std::cerr << "Failed add seccomp rule" << std::endl;
		}
	}
};

void seccompExit()
{
	if(!ctx)
		return;
	seccomp_release(ctx);
	cout << "seccompExit" << endl;
};

