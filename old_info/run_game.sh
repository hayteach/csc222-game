#!/usr/bin/env bash
set -euo pipefail

# Find project root by looking for Makefile or CMakeLists.txt
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")" && pwd)"
DIR="$SCRIPT_DIR"
while [ "$DIR" != "/" ] && [ ! -f "$DIR/Makefile" ] && [ ! -f "$DIR/CMakeLists.txt" ]; do
  DIR="$(dirname "$DIR")"
done

if [ -f "$DIR/Makefile" ]; then
  echo "Building with Makefile in $DIR"
  # Prefer a 'run' target if present, otherwise build all
  if make -C "$DIR" run 2>/dev/null; then
    exit 0
  fi
  make -C "$DIR"
  if [ -x "$DIR/dungeongame/bin/dungeongame" ]; then
    printf "6\n" | "$DIR/dungeongame/bin/dungeongame"
    exit 0
  fi
  echo "Error: binary not found after make in $DIR" >&2
  exit 1

elif [ -f "$DIR/CMakeLists.txt" ]; then
  echo "Building with CMake in $DIR/build"
  mkdir -p "$DIR/build"
  cmake -S "$DIR" -B "$DIR/build" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
  cmake --build "$DIR/build"
  if [ -x "$DIR/dungeongame/bin/dungeongame" ]; then
    printf "6\n" | "$DIR/dungeongame/bin/dungeongame"
    exit 0
  elif [ -x "$DIR/build/dungeongame" ]; then
    printf "6\n" | "$DIR/build/dungeongame"
    exit 0
  fi
  echo "Error: built binary not found after CMake build" >&2
  exit 1

else
  echo "Error: no Makefile or CMakeLists.txt found in any parent of $SCRIPT_DIR" >&2
  exit 1
fi
