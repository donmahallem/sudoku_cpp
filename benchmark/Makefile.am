.PHONY: all test benchmarka


SRCDIR = ../src
BUILDDIR = build
TESTBUILDDIR = build
TESTSRCDIR = ./
TARGET = main
GTESTDIR = ../googletest/googletest
GBENCHMARKDIR = ../googlebenchmark
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
    $(wildcard $(SRCDIR)/models/*.cpp)
TESTSOURCES = $(wildcard $(TESTSRCDIR)/*.cpp)\
    $(wildcard $(TESTSRCDIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TESTOBJECTS = $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTBUILDDIR)/%.o,$(TESTSOURCES))
GTESTHEADERS = $(GTESTDIR)/include/gtest/*.h \
                $(GTESTDIR)/include/gtest/internal/*.h
GTESTSRCS = $(GTESTDIR)/src/*.cc $(GTESTDIR)/src/*.h $(GTESTHEADERS)

GBENCHMARKHEADERS = $(GBENCHMARKDIR)/include/benchmark/*.h 
GBENCHMARKSRCS = $(GBENCHMARKDIR)/src/*.cc $(GBENCHMARKDIR)/src/*.h $(GBENCHMARKHEADERS)

CXXFLAGS = -Wall -std=gnu++11 -g -isystem $(GTESTDIR)/include


buildTestFile: $(TESTOBJECTS) $(filter-out $(BUILDDIR)/main.o, $(OBJECTS)) $(TESTBUILDDIR)/gtest_main.a
	@echo NO IDEA $(OBJECTS)
	@echo NO IDEA2 $(TESTOBJECTS)
	@echo NO IDEA3 $(filter-out $(BUILDDIR)/main.o, $(OBJECTS))
	@echo NO IDEA3 $(TESTBUILDDIR)/gtest_main.a $(RANDOMDAT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $(TESTBUILDDIR)/test

buildGtestLib: $(TESTBUILDDIR)/gtest_main.a

all: $(TESTBUILDDIR)/gtest_main.a benchmarka
	@echo skip9


benchmarka: $(TESTBUILDDIR)/gtest_main.a 
	@echo skip923
    $(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTESTDIR)/include -std=c++11 -lpthread -O2 $(GBENCHMARKSRCS) $(TESTBUILDDIR)/gtest_main.a  -o benchmarka.exe

clean:
	$(RM) $(ALL) *.o
#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@


$(TESTBUILDDIR)/gtest-all.o : $(GTESTSRCS)
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -I$(GTESTDIR) $(CXXFLAGS) -c \
            $(GTESTDIR)/src/gtest-all.cc -o $@
$(TESTBUILDDIR)/gtest_main.o : $(GTESTSRCS)
	$(CXX) $(CPPFLAGS) -I$(GTESTDIR) $(CXXFLAGS) -c \
            $(GTESTDIR)/src/gtest_main.cc -o $@
$(TESTBUILDDIR)/gtest.a : $(TESTBUILDDIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
$(TESTBUILDDIR)/gtest_main.a : $(TESTBUILDDIR)/gtest-all.o $(TESTBUILDDIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(TESTBUILDDIR)/%.o : $(TESTSRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@
    
$(BUILDDIR)/%.o: $(GBENCHMARKDIR)/src/%.cc
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@