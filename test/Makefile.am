.PHONY: all test


SRCDIR = ../src
BUILDDIR = ./build
TESTSRCDIR = .
TARGET = main
GTESTDIR = ../googletest/googletest
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
    $(wildcard $(SRCDIR)/models/*.cpp)
TESTSOURCES = $(wildcard $(TESTSRCDIR)/*.cpp)\
    $(wildcard $(TESTSRCDIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TESTOBJECTS = $(patsubst $(TESTSRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(TESTSOURCES))
GTESTHEADERS = $(GTESTDIR)/include/gtest/*.h \
                $(GTESTDIR)/include/gtest/internal/*.h
GTESTSRCS = $(GTESTDIR)/src/*.cc $(GTESTDIR)/src/*.h $(GTESTHEADERS)


CXXFLAGS = -Wall -std=gnu++11 -g -isystem $(GTESTDIR)/include

buildTestFile: $(TESTOBJECTS) $(OBJECTS) $(BUILDDIR)/gtest_main.a
	@echo NO IDEA $(OBJECTS)
	@echo NO IDEA2 $(TESTOBJECTS)
	@echo NO IDEA3 $(filter-out $(BUILDDIR)/main.o, $(OBJECTS))
	@echo NO IDEA3 $(TESTBUILDDIR)/gtest_main.a $(RANDOMDAT)
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) -I $(SRCDIR) -lpthread $^ -o $(BUILDDIR)/test

buildGtestLib: $(BUILDDIR)/gtest_main.a

all: $(BUILDDIR)/gtest_main.a test
	@echo skip

test: buildTestFile Makefile.am

clean:
	$(RM) $(ALL) *.o

#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@


$(BUILDDIR)/gtest-all.o : $(GTESTSRCS)
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -I$(GTESTDIR) $(CXXFLAGS) -c \
            $(GTESTDIR)/src/gtest-all.cc -o $@
$(BUILDDIR)/gtest_main.o : $(GTESTSRCS)
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -I$(GTESTDIR) $(CXXFLAGS) -c \
            $(GTESTDIR)/src/gtest_main.cc -o $@
$(BUILDDIR)/gtest.a : $(BUILDDIR)/gtest-all.o
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^
$(BUILDDIR)/gtest_main.a : $(BUILDDIR)/gtest-all.o $(BUILDDIR)/gtest_main.o
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^


$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@
$(BUILDDIR)/models/%.o : $(SRCDIR)/models/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@
$(BUILDDIR)/%.o : $(TESTSRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) -I $(SRCDIR) $(CPPFLAGS) $< -c -o $@