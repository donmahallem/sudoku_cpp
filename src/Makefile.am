CXXFLAGS = -Wall -std=gnu++11 -g


SRCDIR = ./
BUILDDIR = ../build
TARGET = main
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
	 $(wildcard $(SRCDIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TESTOBJECTS = $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTBUILDDIR)/%.o,$(TEST_SOURCES))
all: $(OBJECTS) buildExecutable

clean:
	$(RM) $(ALL) -r $(BUILDDIR)/*

#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@
$(BUILDDIR)/models/%.o : $(SRCDIR)/models/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@


buildExecutable: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $^ -o $(BUILDDIR)/test