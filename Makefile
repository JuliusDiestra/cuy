# Variables
BIN_NAME = cuy
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
VERSION := $(shell cat VERSION)
CFLAGS = -O3 -Wall -DCUY_VERSION=\"$(VERSION)\"
LDFLAGS =

SOURCES = main arg_parser status_code cli print_help print_version
OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SOURCES)))

.PHONE:
all: $(SOURCES) $(BIN_NAME)

# Linking
.PHONY:
$(BIN_NAME): $(BIN_DIR)/$(BIN_NAME)
$(BIN_DIR)/$(BIN_NAME): $(OBJECTS) | bin_dir
	gcc $(OBJECTS)  $(LDFLAGS) -o $@

# Compilation
.PHONY: $(SOURCES)
$(SOURCES): %: $(OBJ_DIR)/%.o

$(OBJ_DIR)/%.o: src/%.c | obj_dir
	gcc -c $< $(CFLAGS) -I include -MMD -MP -o $@

-include $(OBJ_DIR)/*.d

# Build dir
.PHONY:
build_dir: $(BUILD_DIR)
$(BUILD_DIR): obj_dir bin_dir

# Objects dir
.PHONY:
obj_dir: $(OBJ_DIR)
$(OBJ_DIR):
	mkdir -p $@

# Binary dir
.PHONY:
bin_dir: $(BIN_DIR)
$(BIN_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	@echo "Cleaning $(BUILD_DIR) directory..."
	@rm -rf $(BUILD_DIR)

