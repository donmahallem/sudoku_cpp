.DEFAULT_GOAL := main
CXXFLAGS = -Wall -std=gnu++11 -g


SRC_DIR = src
TEST_SRC_DIR = test
BUILD_DIR = build
TEST_BUILD_DIR = buildTest
TARGET = main
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)\
	 $(wildcard $(SRC_DIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TEST_SOURCES = $(wildcard $(TEST_SRC_DIR)/*.cpp)\
	 $(wildcard $(TEST_SRC_DIR)/models/*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_BUILD_DIR)/%.o,$(TEST_SOURCES))
CPPFLAGS += -isystem $(GTEST_DIR)/include -pthread -fprofile-arcs -ftest-coverage
GTEST_DIR = googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
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

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(TEST_BUILD_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $@
$(TEST_BUILD_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $@
$(TEST_BUILD_DIR)/gtest.a : $(TEST_BUILD_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
$(TEST_BUILD_DIR)/gtest_main.a : $(TEST_BUILD_DIR)/gtest-all.o $(TEST_BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
####
buildall: $(OBJECTS)
	@echo Combine object files $^
#	ld -r -o build/outa $^
	$(CXX) $(CXXFLAGS) $^ -o build/out -I src

$(TEST_BUILD_DIR)/%.o: test/%.cpp Makefile.mk
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -c -o $@ -I googletest/googletest/include  -I src -I src/models

$(TEST_BUILD_DIR): $(TEST_OBJECTS)

test: $(TEST_OBJECTS) $(filter-out build/main.o, $(OBJECTS)) $(TEST_BUILD_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $(TEST_BUILD_DIR)/test.exe
test2: buildall $(TEST_BUILD_DIR)
	@echo $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_BUILD_DIR)/test.exe $(TEST_SOURCES) $(filter-out src/main.cpp, $(SOURCES)) -I googletest/googletest/include -I src -I src/models
#	$(CXX) $(CXXFLAGS) -o buildTest/test.exe $(TEST_OBJECTS) $(filter-out build/main.o, $(OBJECTS))# -I googletest/googletest/include -I src -I src/models
