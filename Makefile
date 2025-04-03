CXX      := g++                  
CXXFLAGS := -Wall -Wextra -Werror
LDFLAGS  := -lm                  
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)
TARGET   := app
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/*.cpp)

OBJECTS := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: clean build $(APP_DIR)/$(TARGET) run

$(OBJ_DIR)/%.o: src/%.cpp 
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O3
release: all

clean:
	@rm -rvf $(OBJ_DIR) $(APP_DIR)/$(TARGET)

run:
	@echo "Running application..."
	@./$(APP_DIR)/$(TARGET)