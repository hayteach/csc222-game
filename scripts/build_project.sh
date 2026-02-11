#!/usr/bin/env bash
set -euo pipefail

# Build all dungeongame source files that do NOT define main()
# This keeps wildcard behavior but prevents duplicate main() at link time.

SRCDIR="dungeongame/src"
OUTDIR="dungeongame/bin"
INCDIR="dungeongame/include"

mkdir -p "${OUTDIR}"

# Collect sources, include main.cpp but skip other files that contain "int main("
sources=()
for f in "${SRCDIR}"/*.cpp; do
  base=$(basename "$f")
  if [ "$base" = "main.cpp" ]; then
    # Ensure main.cpp is included (this project uses this as the program entry)
    sources+=("$f")
    continue
  fi
  if grep -qE "int[[:space:]]+main[[:space:]]*\(" "$f"; then
    echo "Skipping $f (contains main)"
    continue
  fi
  sources+=("$f")
done

if [ ${#sources[@]} -eq 0 ]; then
  echo "No source files to compile"
  exit 1
fi

echo "Compiling: ${sources[*]}"

# Use clang++ if available, otherwise fall back to g++
CXX="$(command -v clang++ || command -v g++ || true)"
if [ -z "$CXX" ]; then
  echo "No suitable C++ compiler found (clang++ or g++ required)" >&2
  exit 2
fi

"$CXX" -fcolor-diagnostics -fansi-escape-codes -g "${sources[@]}" -I "${INCDIR}" -I "${INCDIR}/dungeongame" -o "${OUTDIR}/dungeongame"

echo "Built ${OUTDIR}/dungeongame with $CXX"