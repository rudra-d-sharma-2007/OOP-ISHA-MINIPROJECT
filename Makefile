CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS += -Iinclude -MMD -MP

TARGET := translation_sim
SRC    := $(wildcard src/*.cpp)
OBJ    := $(SRC:src/%.cpp=build/%.o)
DEP    := $(OBJ:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

build/%.o: src/%.cpp | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

run: $(TARGET)
	./$(TARGET)

# Capture the program's frame output for the browser page (app/index.html).
web: $(TARGET)
	./$(TARGET) 200 10 > app/output.txt
	@echo "wrote app/output.txt ($$(wc -l < app/output.txt) lines)"

clean:
	rm -rf build $(TARGET) app/output.txt

-include $(DEP)

.PHONY: all run web clean
