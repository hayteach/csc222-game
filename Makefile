# Simple Makefile for dungeongame (macOS / Linux / WSL / MSYS)
CC = g++
# Application name can be overridden with `make APP=name`. Defaults to dungeongame.
APP ?= dungeongame

# Include both the include root and the nested project folder so headers
# like "Player.h" (located at dungeongame/include/dungeongame/Player.h)
# are found when compiling from the repo root.  You can override the include
# path by setting INCDIR, e.g. `make INCDIR=some/other/dir`.
INCDIR ?= dungeongame/include
# Compiler flags: can be overridden by passing CFLAGS on the make command line
# (e.g. `make CFLAGS="-O2 -std=c++20"`).  We add include paths only if the
# directories actually exist, so the recipe works in projects without a
# dedicated include directory.  The APP variable determines the second path.

# helper to test for a directory and produce an -I flag if present
ifeq ($(wildcard $(INCDIR)),)
INCDIRFLAG :=
else
INCDIRFLAG := -I $(INCDIR)
endif

ifeq ($(wildcard $(INCDIR)/$(APP)),)
APPINCDIRFLAG :=
else
APPINCDIRFLAG := -I $(INCDIR)/$(APP)
endif

CFLAGS ?= -std=c++17 $(INCDIRFLAG) $(APPINCDIRFLAG) -g -Wall
# Source directory can be overridden if the project layout differs; fall back
# to the app-specific "src" subdirectory.  If your project doesn't have a
# dedicated source folder you can invoke `make SRCDIR=.`, or simply set
# `SOURCES` directly on the command line.
SRCDIR ?= $(APP)/src

# Build source list.  By default we pick up everything in SRCDIR; earlier
# versions explicitly included main.cpp but student projects may place the
# `main()` function in any file.  If you have more than one translation unit
# containing `main` or want a nonstandard layout, simply set SOURCES on the
# command line (e.g. `make SOURCES="foo.cpp bar.cpp"`).
#
# We still filter out obvious demo files so temporary examples don't end up in
# the build.
SOURCES := $(filter-out $(SRCDIR)/*_demo.cpp $(SRCDIR)/pointers_demo.cpp, $(wildcard $(SRCDIR)/*.cpp))

# NOTE: if SRCDIR='.' or you override SOURCES manually, the above pattern may
# not be suitable; again, you can supply SOURCES yourself.

# output binary is in bin/<app-name>
TARGET = bin/$(APP)

.PHONY: all clean run
# Default target builds the application.  If you set RUN_ON_BUILD to any
# nonempty value the binary will be executed immediately after a successful
# build (mirroring the behavior of the platform-specific scripts).
all: $(TARGET)
	@if [ -n "$(RUN_ON_BUILD)" ]; then \
		echo "Running $(TARGET) as requested..."; \
		./$(TARGET); \
	fi

$(TARGET): $(SOURCES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf bin
