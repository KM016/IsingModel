# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Target executable for 1D simulation
TARGET = IsingSim1D

# Source files for 1D
SOURCES = 1D_main.cpp IsingModel.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Testing mode for 1D 
test1:
	$(CXX) $(CXXFLAGS) -DTEST -o 1D_test 1D_main.cpp IsingModel.cpp
	./1D_test

clean:
	rm -f $(OBJECTS) $(TARGET) ./1D_test