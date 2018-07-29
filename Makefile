.DEFAULT_GOAL := main
CXXFLAGS = -g -Wall -std=c++11

TARGET = main
OBJECTS = src/models/sudoku_field.cpp src/models/sudoku_tip_field.cpp src/models/tip_info.cpp src/sudoku_solver.cpp
all: $(TARGET)

$(TARGET): src/main.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ src/$@.cpp $(OBJECTS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $<
clean:
	$(RM) $(ALL) *.o

test: all
	$(CXX) $(CXXFLAGS) -o $@ test/$@.cpp $(OBJECTS) -I googletest/googletest/include src