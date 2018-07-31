.DEFAULT_GOAL := main
SRCDIR = src
BUILDDIR = build
CXXFLAGS = -g -Wall -std=gnu++11 -I $(src)
TARGET = main
SOURCES = $(wildcard $(SRCDIR)/*.cpp)\
	 $(wildcard $(SRCDIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET):$(OBJECTS) Makefile.mk
	@echo Compiling $< into $@
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

#$(TARGET): src/main.cpp Makefile.mk
#	@echo Compiling $(SOURCES) $(OBJECTS)
#	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)


all: $(OBJECTS)
	$(CCX) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CCX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@
clean:
	$(RM) $(ALL) *.o

test: all
	$(CXX) $(CXXFLAGS) -o $@ test/$@.cpp $(OBJECTS) -I googletest/googletest/include -I src