# all:
# 	g++ -std=c++17 src/main.cpp -o build/gscripts

# CXX = g++
# CXXFLAGS = -std=c++17 -Wall
# SRC_DIR = src
# BUILD_DIR = build

# SOURCES = \
# 	$(SRC_DIR)/main.cpp \
# 	$(SRC_DIR)/lexer/tokenizer.cpp \
# 	$(SRC_DIR)/parser/parser.cpp \
# 	${SRC_DIR}/codegen/codegen.cpp

# EXECUTABLE = $(BUILD_DIR)/gscript

# all:
# 	mkdir -p $(BUILD_DIR)
# 	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

# clean:
# 	rm -rf $(BUILD_DIR)

SRC_DIR = src
BUILD_DIR = build

SOURCES = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/lexer/tokenizer.cpp \
	$(SRC_DIR)/parser/parser.cpp \
	$(SRC_DIR)/codegen/codegen.cpp

EXECUTABLE = $(BUILD_DIR)/gscript
RUNNER = gscript-run

all:
	mkdir -p $(BUILD_DIR)
	g++ -std=c++17 -Wall $(SOURCES) -o $(EXECUTABLE)
	g++ -std=c++17 -Wall gscript-run.cpp -o gscript-run

install:
	sudo cp gscript-run /usr/local/bin/gsc
	@echo "✅ GScript compiler installed as 'gsc'."
	@echo "💡 Try: gsc examples/hello.gscript"

clean:
	rm -rf $(BUILD_DIR) gscript-run
