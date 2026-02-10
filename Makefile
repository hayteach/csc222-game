CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I dungeongame/include -I dungeongame/include/dungeongame

# Sources
SRC = $(wildcard dungeongame/src/*.cpp)
SRCS_LIB = $(filter-out dungeongame/src/main.cpp dungeongame/src/pointers_demo.cpp, $(SRC))
TEST_SRC = dungeongame/tests/combat_test.cpp dungeongame/tests/test_inventory.cpp dungeongame/tests/test_enemygroup.cpp
TEST_BIN = $(BIN_DIR)/combat_test

# Binaries
BIN_DIR = dungeongame/bin
BIN = $(BIN_DIR)/dungeongame
POINTERS_BIN = $(BIN_DIR)/pointers_demo

# Objects go to a separate directory to keep sources clean
# This prevents object files from cluttering the source tree and makes it easy
# to clean or reuse build artifacts for different configurations.
OBJ_DIR = dungeongame/obj
OBJS = $(patsubst dungeongame/src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS_LIB))

all: $(BIN) $(TEST_BIN) $(POINTERS_BIN)

# Main binary links with library objects
$(BIN): $(OBJS) dungeongame/src/main.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN) dungeongame/src/main.cpp $(OBJS)

# Test binary links with library objects
$(TEST_BIN): $(OBJS) $(TEST_SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(OBJS)

# Pointers demo (interactive)
$(POINTERS_BIN): $(OBJS) dungeongame/src/pointers_demo.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(POINTERS_BIN) dungeongame/src/pointers_demo.cpp $(OBJS)

# Compile object files into OBJ_DIR
$(OBJ_DIR)/%.o: dungeongame/src/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run both tests and game (auto-quit)
test: all
	$(TEST_BIN)
	printf "6\n" | $(BIN)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) *.o

.PHONY: all clean test
