# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

# Directories
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin
BUILD_TEST_DIR = build/tests

# Output files
APP = $(BIN_DIR)/app
TEST_APP = $(BUILD_TEST_DIR)/test_app

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ_FILES = $(SRC_FILES:.cpp=.o)
TEST_OBJ_FILES = $(TEST_FILES:.cpp=.o)

# Targets
.PHONY: all clean run test

all: $(APP)

# Build the main application
$(APP): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the main application
run: $(APP)
	./$(APP)

# Build and run tests
test: $(TEST_APP)
	./$(TEST_APP)

$(TEST_APP): $(TEST_OBJ_FILES)
	@mkdir -p $(BUILD_TEST_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Clean up generated files
clean:
	rm -rf $(OBJ_FILES) $(TEST_OBJ_FILES) $(APP) $(TEST_APP) $(BIN_DIR) $(BUILD_TEST_DIR)