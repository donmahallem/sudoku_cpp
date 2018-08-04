


SRCDIR = ../src
BUILDDIR = ../build
TESTBUILDDIR = ../buildTest
TESTSRCDIR = ./
TARGET = main
GTESTDIR = ../googletest/googletest
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
    $(wildcard $(SRCDIR)/models/*.cpp)
TESTSOURCES = $(wildcard $(TESTSRCDIR)/*.cpp)\
    $(wildcard $(TESTSRCDIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TESTOBJECTS = $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTBUILDDIR)/%.o,$(TESTSOURCES))
GTESTHEADERS = $(GTESTDIR)/include/gtest/*.h \
                $(GTESTDIR)/include/gtest/internal/*.h
GTESTSRCS = $(GTESTDIR)/src/*.cc $(GTESTDIR)/src/*.h $(GTESTHEADERS)


CXXFLAGS = -Wall -std=gnu++11 -g -isystem $(GTESTDIR)/include

buildTestFile: $(TESTOBJECTS) $(filter-out $(BUILDDIR)/main.o, $(OBJECTS)) $(TESTBUILDDIR)/gtest_main.a
	@echo NO IDEA $(OBJECTS)
	@echo NO IDEA2 $(TESTOBJECTS)
	@echo NO IDEA3 $(filter-out $(BUILDDIR)/main.o, $(OBJECTS))
	@echo NO IDEA3 $(TESTBUILDDIR)/gtest_main.a $(RANDOMDAT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) -lpthread $^ -o $(TESTBUILDDIR)/test

buildGtestLib: $(TESTBUILDDIR)/gtest_main.a

all: buildTestFile

clean:
	$(RM) $(ALL) *.o

#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@


$(TESTBUILDDIR)/gtest-all.o : $(GTESTSRCS)
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