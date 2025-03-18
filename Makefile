# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Target executable
TARGET = IsingModel

# Source files (now in the src folder)
SOURCES = src/main.cpp src/IsingModel.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target: build the executable
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Testing
test:
	$(CXX) $(CXXFLAGS) -DTEST -o IsingTests src/main.cpp src/IsingModel.cpp
	./IsingTests TEST

# Clean target to remove objects and executables
clean:
	rm -f $(OBJECTS) $(TARGET) Ising_tests
