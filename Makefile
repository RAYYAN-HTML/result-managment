.PHONY: build clean run help install

# Directories
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
SRC_DIR := src
INCLUDE_DIR := include

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -I$(INCLUDE_DIR)
LDFLAGS := 

# Source files and objects
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE := $(BIN_DIR)/result_management

# Default target
all: build

# Build target
build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Build complete: $(EXECUTABLE)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run target
run: build
	@$(EXECUTABLE)

# Clean target
clean:
	@rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned build artifacts"

# Install target (optional)
install: build
	@mkdir -p /usr/local/bin
	@cp $(EXECUTABLE) /usr/local/bin/result_management
	@echo "✓ Installed to /usr/local/bin/result_management"

# Help target
help:
	@echo "Available targets:"
	@echo "  make build    - Build the project"
	@echo "  make run      - Build and run the application"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make install  - Install to /usr/local/bin"
	@echo "  make help     - Display this help message"
