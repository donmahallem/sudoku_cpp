.DEFAULT_GOAL := main
CXXFLAGS = -Wall -std=gnu++11 -g


SRC_DIR = src
BUILD_DIR = build
TARGET = main
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)\
	 $(wildcard $(SRC_DIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
#OBJECTS = src/models/sudoku_field.cpp src/models/sudoku_tip_field.cpp src/models/tip_info.cpp src/sudoku_solver.cpp
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $(SOURCES)

clean:
	$(RM) $(ALL) *.o

#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@

build/%.o : src/%.cpp Makefile.mk
	$(CXX) $(CXXFLAGS) $< -c -o $@
build/models/%.o : src/models/%.cpp Makefile.mk
	$(CXX) $(CXXFLAGS) $< -c -o $@

a: $(OBJECTS)

buildall: $(OBJECTS)
	@echo Combine object files $^
#	ld -r -o build/outa $^
	$(CXX) $(CXXFLAGS) $^ -o build/out -I src
test: all
	$(CXX) $(CXXFLAGS) -o $@ test/$@.cpp -I googletest/googletest/include -I src -I src/models