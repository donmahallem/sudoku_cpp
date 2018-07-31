CC          = g++
LD          = g++ 
CFLAG       = -Wall
PROG_NAME   = prog

SRC_DIR     = ./src
BUILD_DIR   = ./build
BIN_DIR     = ./bin
SRC_LIST = $(wildcard $(SRC_DIR)/*.cpp)
SRC_LIST = $(wildcard $(SRC_DIR)/*.cpp)\
	 $(wildcard $(SRC_DIR)/models/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
OBJ_LIST = $(BUILD_DIR)/$(notdir $(SRC_LIST:.cpp=.o))

.PHONY: all clean $(PROG_NAME) compile

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I$(SRC_DIR) -c $< -o $@
clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*.o