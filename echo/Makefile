.PHONY: all debug release clean

Compiler = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS = -g -O0 -Wall
RELEASE_EXEC = ech0
DEBUG_EXEC = ech0-dbg
SOURCE = ech0.cpp

all: debug release

debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): $(SOURCE)
	$(Compiler) $(DEBUG_FLAGS) $(SOURCE) -o $(DEBUG_EXEC)

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(SOURCE)
	$(Compiler) $(RELEASE_FLAGS) $(SOURCE) -o $(RELEASE_EXEC)

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC)
