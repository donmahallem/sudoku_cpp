.DEFAULT_GOAL := main
SRCDIR = src
BUILDDIR = build
CXXFLAGS = -g -Wall -std=gnu++11 -I $(src)
TEST_CXXFLAGS =$(CXXFLAGS) -pthread -I -fprofile-arcs -ftest-coverage
TARGET = main
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
	 $(wildcard $(SRCDIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
CPPFLAGS += -isystem $(GTEST_DIR)/include
GTEST_DIR = googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
all: $(TARGET)

$(TARGET):$(OBJECTS) Makefile.mk
	@echo Compiling $< into $@
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

#$(TARGET): src/main.cpp Makefile.mk
#	@echo Compiling $(SOURCES) $(OBJECTS)
#	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)



# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
buildTest/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc
buildTest/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc
buildTest/gtest.a : buildTest/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
buildTest/gtest_main.a : buildTest/gtest-all.o buildTest/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

all: $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c Makefile.mk
	$(CCX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@
clean:
	$(RM) $(ALL) *.o

test: all $(TEST_OBJECTS) $(filter-out build/main.o, $(OBJECTS)) buildTest/gtest_main.a Makefile.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
test2: all
	$(CXX) $(TEST_CXXFLAGS) -o $@ test/$@.cpp $(OBJECTS) -I googletest/googletest/include -I src