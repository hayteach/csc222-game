# Simple Makefile for dungeongame (macOS / Linux / WSL / MSYS)
CC = g++
# Include both the include root and the nested project folder so headers
# like "Player.h" (located at dungeongame/include/dungeongame/Player.h)
# are found when compiling from the repo root.
CFLAGS = -std=c++17 -I dungeongame/include -I dungeongame/include/dungeongame -g -Wall
SRCDIR = dungeongame/src
# Build source list: include main.cpp explicitly and filter out obvious demo files
# (e.g., *_demo.cpp or pointers_demo.cpp) so wildcard behavior still picks up new
# student source files while avoiding files intended as separate executables.
SOURCES := $(SRCDIR)/main.cpp $(filter-out $(SRCDIR)/main.cpp $(SRCDIR)/*_demo.cpp $(SRCDIR)/pointers_demo.cpp, $(wildcard $(SRCDIR)/*.cpp))
TARGET = bin/dungeongame

.PHONY: all clean run
all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf bin
