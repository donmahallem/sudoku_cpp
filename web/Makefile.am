.PHONY: web

CXXFLAGS = -Wall -std=gnu++11 -g

SRCDIR = ../src
BUILDDIR = ../build
BUILDDIREMSCRIPTEN = ../buildWeb
TARGET = main
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
	 $(wildcard $(SRCDIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
OBJECTSEMSCRIPTEN = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIREMSCRIPTEN)/%.bc,$(SOURCES))
TESTOBJECTS = $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTBUILDDIR)/%.o,$(TEST_SOURCES))


OBJECTSNOMAIN = $(filter-out $(BUILDDIREMSCRIPTEN)/main.o, $(OBJECTSEMSCRIPTEN))
clean:
	$(RM) $(ALL) -r $(BUILDDIREMSCRIPTEN)/*

#$(OBJECTS) : $(SOURCES) Makefile.mk
#	@echo $(SOURCES)
#	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@
$(BUILDDIR)/models/%.o : $(SRCDIR)/models/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPCOVERAGEFLAGS) $(CPPFLAGS) $< -c -o $@


# EMSCRIPTEN SPECIFIC
$(BUILDDIREMSCRIPTEN)/%.bc : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	emcc -O2 $< -o $@
$(BUILDDIREMSCRIPTEN)/models/%.bc : $(SRCDIR)/models/%.cpp
	@mkdir -p $(@D)
	emcc -O2 $< -o $@

buildEmscripten: $(OBJECTSNOMAIN)
#	emcc -02 $^ -o $(BUILDDIREMSCRIPTEN)/project.html
	em++ --bind -o $(BUILDDIREMSCRIPTEN)/quick_example.js web.cpp $(OBJECTSNOMAIN) --std=c++11

all: buildEmscripten