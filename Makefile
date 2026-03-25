# Variables
BIN_NAME = cuy
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj
TEST_BIN_DIR = $(BUILD_DIR)/test_bin
VERSION := $(shell cat VERSION)
CFLAGS = -O3 -Wall -MMD -MP
CXXFLAGS = -O3 -Wall -MMD -MP
CPPFLAGS = -Iinclude -DCUY_VERSION=\"$(VERSION)\"
LDFLAGS =
LDFLAGS_TEST = -lgtest -lgtest_main

DOCKER_FILE = Dockerfile
DOCKER_IMAGE = cuy-image
DOCKER_CONTAINER = cuy-container

SOURCES = main arg_parser status_code cli print_help print_version file_handler lines
OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SOURCES)))

.PHONY: all clean test
.PHONY: obj_dir bin_dir test_bin_dir test_obj_dir
.PHONY: test_file_handler

all: $(BIN_NAME) test

# Linking
$(BIN_NAME): $(BIN_DIR)/$(BIN_NAME)
$(BIN_DIR)/$(BIN_NAME): $(OBJECTS) | bin_dir
	gcc $(OBJECTS)  $(LDFLAGS) -o $@

# Compilation
$(SOURCES): %: $(OBJ_DIR)/%.o

$(OBJ_DIR)/%.o: src/%.c | obj_dir
	gcc -c $< $(CPPFLAGS) $(CFLAGS) -o $@

-include $(OBJ_DIR)/*.d

# Build dir
build_dir: $(BUILD_DIR)
$(BUILD_DIR): obj_dir bin_dir

# Objects dir
obj_dir: $(OBJ_DIR)
$(OBJ_DIR):
	mkdir -p $@

# Binary dir
bin_dir: $(BIN_DIR)
$(BIN_DIR):
	mkdir -p $@

clean:
	@echo "Cleaning $(BUILD_DIR) directory..."
	@rm -rf $(BUILD_DIR)

# ---------- unit-test ---------------------
test: $(TEST_BIN_DIR)/test_file_handler
	@echo "Running tests..."
	@$(TEST_BIN_DIR)/test_file_handler

# file_handler tests
test_file_handler: $(TEST_BIN_DIR)/test_file_handler
$(TEST_BIN_DIR)/test_file_handler: $(TEST_OBJ_DIR)/test_file_handler.o $(OBJ_DIR)/file_handler.o $(OBJ_DIR)/status_code.o | test_bin_dir
	g++ $^ $(LDFLAGS) $(LDFLAGS_TEST) -o $@

$(TEST_OBJ_DIR)/test_file_handler.o: test/test_file_handler.cpp | test_obj_dir
	g++ -c $< $(CPPFLAGS) $(CXXFLAGS) -o $@

# Test dirs
test_bin_dir: $(TEST_BIN_DIR)
$(TEST_BIN_DIR):
	mkdir -p $@

test_obj_dir: $(TEST_OBJ_DIR)
$(TEST_OBJ_DIR):
	mkdir -p $@

-include $(TEST_OBJ_DIR)/*.d
