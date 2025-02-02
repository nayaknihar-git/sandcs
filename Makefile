# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Ilib

# Source files
SRCS = src/sandbox.cpp  src/arge_parse.cpp src/seccomp_util.cpp  src/cgroup_util.cpp
SRC2 = src/hello_world.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)

# Define the libraries to link
SECCOMPLIBS = -lseccomp

# Executable name
EXEC = sandbox_test

# TEST Binary
TESTEXEC = hello_world

# Default target
all: $(EXEC) $(TESTEXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(SECCOMPLIBS)

$(TESTEXEC): $(SRC2)
	$(CXX) -o $(TESTEXEC) $(SRC2)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(OBJS2) $(EXEC) $(TESTEXEC)

# Phony targets
.PHONY: all clean
