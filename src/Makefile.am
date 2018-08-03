CXXFLAGS = -Wall -std=gnu++11 -g


SRCDIR = ./
TESTSRCDIR = ../test
BUILDDIR = ../build
TESTBUILDDIR = ../buildTest
TARGET = main
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
	 $(wildcard $(SRCDIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TESTOBJECTS = $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTBUILDDIR)/%.o,$(TEST_SOURCES))
GTESTDIR = ../googletest/googletest
CPPFLAGS = -isystem $(GTESTDIR)/include -pthread $(G_CPP_FLAGS)
GTESTHEADERS = $(GTESTDIR)/include/gtest/*.h \
                $(GTESTDIR)/include/gtest/internal/*.h
GTESTSRCS = $(GTESTDIR)/src/*.cc $(GTESTDIR)/src/*.h $(GTESTHEADERS)
all: $(OBJECTS) Makefile.am Makefile

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) -o $(BUILDDIR)/$@ $(SOURCES)

clean:
	$(RM) $(ALL) *.o

#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@
$(BUILDDIR)/models/%.o : $(SRCDIR)/models/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@

a: $(OBJECTS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
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
####
buildall: $(OBJECTS)
	@echo Combine object files $^
#	ld -r -o build/outa $^
	$(CXX) $(CXXFLAGS) $^ -o build/out -I src

$(TESTBUILDDIR)/%.o: test/%.cpp Makefile.mk
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -c -o $@ -I googletest/googletest/include  -I src -I src/models

$(TESTBUILDDIR): $(TESTOBJECTS)
