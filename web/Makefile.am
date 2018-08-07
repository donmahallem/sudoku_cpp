CXXFLAGS = -Wall -std=gnu++11 -g


SRCDIR = ./
BUILDDIR = ../build
BUILDDIREMSCRIPTEN = ../buildEmscripten
TARGET = main
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
	 $(wildcard $(SRCDIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
OBJECTSEMSCRIPTEN = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIREMSCRIPTEN)/%.bc,$(SOURCES))
TESTOBJECTS = $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTBUILDDIR)/%.o,$(TEST_SOURCES))
all: $(OBJECTS) Makefile.am Makefile

clean:
	$(RM) $(ALL) *.o

#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@
$(BUILDDIR)/models/%.o : $(SRCDIR)/models/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@


# EMSCRIPTEN SPECIFIC
$(BUILDDIREMSCRIPTEN)/%.bc : $(SRCDIR)/%.cpp
	emcc -O2 $< -o $@
$(BUILDDIREMSCRIPTEN)/models/%.bc : $(SRCDIR)/models/%.cpp
	emcc -O2 $< -o $@

buildEmscripten: Makefile.am
#	emcc -02 $^ -o $(BUILDDIREMSCRIPTEN)/project.html
	em++ --bind -o $(BUILDDIREMSCRIPTEN)/quick_example.js web.cpp --std=c++11

html: buildEmscripten Makefile.am