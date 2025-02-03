Build:
The prerequisites to build, following packages need to be installed.
sudo apt install libseccomp-dev
sudo apt install cgroup-tools

To run process under sandbox: 
./sandbox_test -n cgroup_name -m 1024 -c 20 -b "./hello_ward"  -a " argument of bin hello_world"

