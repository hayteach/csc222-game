#!/usr/bin/env bash
set -euo pipefail

# Determine the directory where this script lives
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")" && pwd)"

# Walk up the directory tree until we find a Makefile
DIR="$SCRIPT_DIR"
while [ "$DIR" != "/" ] && [ ! -f "$DIR/Makefile" ]; do
  DIR="$(dirname "$DIR")"
done

if [ ! -f "$DIR/Makefile" ]; then
  echo "Error: Makefile not found in any parent directory of $SCRIPT_DIR" >&2
  exit 1
fi

echo "Building project in $DIR..."
# Use the Makefile's 'test' target (it builds and runs tests + game)
make -C "$DIR" test

echo "Run finished (exit code $? )"