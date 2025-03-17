# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Targets
TARGET_1D = IsingSim1D
TARGET_2D = IsingSim2D

# Source files
SOURCES_1D = 1D_main.cpp IsingModel.cpp
SOURCES_2D = 2D_main.cpp IsingModel.cpp

# Object files
OBJECTS_1D = $(SOURCES_1D:.cpp=.o)
OBJECTS_2D = $(SOURCES_2D:.cpp=.o)

# Build both 1D and 2D executables
all: $(TARGET_1D) $(TARGET_2D)

$(TARGET_1D): $(OBJECTS_1D)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_2D): $(OBJECTS_2D)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Testing mode for 1D 
test1:
	$(CXX) $(CXXFLAGS) -DTEST -o 1D_test 1D_main.cpp IsingModel.cpp
	./1D_test

test2:
	$(CXX) $(CXXFLAGS) -DTEST -o 2D_test 2D_main.cpp IsingModel.cpp
	./2D_test

clean:
	rm -f $(OBJECTS_1D) $(OBJECTS_2D) $(TARGET_1D) $(TARGET_2D) ./1D_test ./2D_test