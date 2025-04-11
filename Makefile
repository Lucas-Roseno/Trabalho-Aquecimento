BUILD     := build
OBJ_DIR   := $(BUILD)/objects
APP_DIR   := $(BUILD)
TARGET    := app
INCLUDE   := -Iinclude/
SRC       := $(wildcard src/*.cpp)
OBJECTS   := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

CXX       := g++
CXXFLAGS  := -Wall -Wextra -Werror
LDFLAGS   := -lm

all: clean $(APP_DIR)/$(TARGET)
	@clear
	@echo "Executando $(APP_DIR)/$(TARGET)..."
	@./$(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@chmod +x $@

clean:
	@rm -rf $(BUILD)

run: $(APP_DIR)/$(TARGET)
	@clear
	@./$(APP_DIR)/$(TARGET)

.PHONY: all clean run
