CC = g++
BUILD_DIR = ./build
INCLUDE_DIR = ./include
LIBRARY_DIR = ./lib
SRC_DIR = ./src
BIN_DIR = ./bin

INCLUDE_FLAGS = -I $(INCLUDE_DIR)
LD_FLAGS = -L $(LIBRARY_DIR)
L_FLAGS = -lmingw32 -lSDL2main -lSDL2
vpath %.cpp $(SRC_DIR)

$(BUILD_DIR)/%.o : %.cpp
	$(CC) -c $(INCLUDE_FLAGS) -o $@ $^

$(BIN_DIR)/% : $(wildcard $(BUILD_DIR)/*.o) 
	$(CC) -g $(LD_FLAGS) -o $@ $^ $(L_FLAGS)

.PHONY : run

% : 
	$(BIN_DIR)/$@
