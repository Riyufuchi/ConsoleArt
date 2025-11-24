# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O3 -std=c++20

# ConsoleArt
SRC_DIR = src
INC_DIR = libs/ConsoleLib/inc
INC_CSDL_DIR = libs/ComponentSDL/inc
BUILD_DIR = build
LIB_DIR = libs/ConsoleLib
LIB_CSDL_DIR = libs/ComponentSDL

# Find all .cpp files
CPP_SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

C_SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.c")

# Combine both .cpp and .c source files
SRC_FILES := $(CPP_SRC_FILES) $(C_SRC_FILES)

# Generate object file names
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Application name
APP_NAME = ConsoleArt
APP_TARGET = $(BUILD_DIR)/$(APP_NAME)

# ConsoleLib
LIB_NAME = ConsoleLib
LIB_FILE_NAME = libConsoleLib.a
LIB_REPO = https://github.com/Riyufuchi/ConsoleLib.git
LIB_PATH = libs-git/$(LIB_NAME)

# ComponentSDL lib
LIB_SDL_NAME = ComponentSDL
LIB_SDL_FILE_NAME = libComponentSDL.a
LIB_SDL_REPO = https://github.com/Riyufuchi/ComponentSDL.git
LIB_SDL_PATH = libs-git/$(LIB_SDL_NAME)

# Default target
all: $(LIB_PATH) $(LIB_SDL_PATH) $(APP_TARGET)

# Link executable
$(APP_TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(LIB_DIR) -L$(LIB_CSDL_DIR) -I$(INC_DIR) -I$(INC_CSDL_DIR) -lConsoleLib -lComponentSDL -lSDL2 -lSDL2_image -lSDL2_ttf
	cp -r assets build

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_CSDL_DIR) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_CSDL_DIR) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

libs: $(LIB_PATH) $(LIB_SDL_PATH)
$(LIB_PATH):
	mkdir -p $(dir libs-git) # Ensure directory exists
	@if [ ! -d "$(LIB_PATH)" ]; then \
		git clone $(LIB_REPO) $(LIB_PATH); \
	else \
		cd $(LIB_PATH) && git pull; \
	fi
	cd $(LIB_PATH) && make
	mkdir -p $(LIB_DIR)
	cd $(LIB_PATH) && cp build/$(LIB_FILE_NAME) ../../libs/ConsoleLib
	cd $(LIB_PATH) && cp -r src/inc ../../libs/ConsoleLib
	
$(LIB_SDL_PATH):
	@if [ ! -d "$(LIB_SDL_PATH)" ]; then \
		git clone $(LIB_SDL_REPO) $(LIB_SDL_PATH); \
	else \
		cd $(LIB_SDL_PATH) && git pull; \
	fi
	cd $(LIB_SDL_PATH) && make
	mkdir -p $(LIB_CSDL_DIR)
	cd $(LIB_SDL_PATH) && cp build/$(LIB_SDL_FILE_NAME) ../../libs/ComponentSDL
	cd $(LIB_SDL_PATH) && cp -r src/inc ../../libs/ComponentSDL

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(APP_TARGET)
	
clean-libs:
	rm -rf $(LIB_PATH) $(LIB_SDL_PATH) libs

# Documentation
docs:
	cd latex-doc && \
	lualatex ConsoleArt.tex && \
	makeglossaries ConsoleArt && \
	lualatex ConsoleArt.tex && \
	lualatex ConsoleArt.tex

.PHONY: all clean docs libs

