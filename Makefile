# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Target executable
TARGET = pocketmons.exe

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
ASSETS_DIR = assets

$(TARGET): src/main.cpp
	set TMPDIR=./temp && set TMP=./temp && set TEMP=./temp && $(CXX) $(CXXFLAGS) src/main.cpp -o $(TARGET) $(LIBS)

clean:
	del $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean test run debug release