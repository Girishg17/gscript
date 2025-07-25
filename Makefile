# all:
# 	g++ -std=c++17 src/main.cpp -o build/gscripts

CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC_DIR = src
BUILD_DIR = build

SOURCES = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/lexer/tokenizer.cpp \
	$(SRC_DIR)/parser/parser.cpp

EXECUTABLE = $(BUILD_DIR)/gscript

all:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)
