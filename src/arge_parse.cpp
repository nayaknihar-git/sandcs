#include<bits/stdc++.h>
using namespace std;

void printHelp();
int  arg_parse(char* argv[], int argc, map<string, string> &options);

void printHelp()
{
    std::cout << "Usage: program [options]\n"
              << "Options:\n"
              << "  -h, --help          Show this help message\n"
              << "  -m, --memory        memory limits in bytes\n"
              << "  -c, --cpu           cpu limits in percantage\n"
              << "  -b, --binary        name of Binary to be sandboxed\n"
              << "  -a, --arg           arg of Binary to be sandboxed\n"
              << "  -o, --output FILE   Specify output file\n"
              << "  -v, --verbose       Enable verbose mode\n"
              << "  -n, --number NUM    Specify a number\n";
}

int  arg_parse(char* argv[], int argc, map<string, string> &options)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") {
			printHelp();
			return 0;
		} else if (arg == "-m" || arg == "--memory")
		{
			if (i + 1 < argc)
			{
				options["memory"] = argv[++i];
			}
			else
			{
				std::cerr << "Error: limiting no of bytes " << arg << std::endl;
				return 1;
			}
		} else if (arg == "-c" || arg == "--cpu")
		{
			if (i + 1 < argc)
			{
				options["memory"] = argv[++i];
			} else
			{
				std::cerr << "Error: cpu percentage " << arg << std::endl;
				return 1;
			}
		} else if (arg == "-b" || arg == "--binary")
		{
			if (i + 1 < argc)
			{
				options["bin"] = argv[++i];
			}
		        else
			{
				std::cerr << "Error: name of binary to be sandboxed" << arg << std::endl;
				return 1;
			}

		} else if (arg == "-a" || arg == "--arg")
		{
			if (i + 1 < argc) {
				options["arg"] = argv[++i];
			}
			else
			{
				std::cerr << "Error: arg of Binary to be sandboxed " << arg << std::endl;
				return 1;
			}
		} else if (arg == "-n" || arg == "--number")
		{
	    		if (i + 1 < argc)
			{
				options[arg] = argv[++i];
			}
			else
			{
				std::cerr << "Error: Missing value for " << arg << std::endl;
				return 1;
		        }
		}
	}
	return 0;
}
