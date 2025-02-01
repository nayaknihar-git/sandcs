# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Ilib

# Source files
SRCS = src/sandbox.cpp  src/seccomp_util.cpp  src/cgroup_util.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Define the libraries to link
SECCOMPLIBS = -lseccomp

# Executable name
EXEC = sandbox_test

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(SECCOMPLIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean
