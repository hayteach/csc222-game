#!/usr/bin/env bash
# Helper launcher: prefer python3, fall back to python, otherwise show message.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
if command -v python3 >/dev/null 2>&1; then
  python3 "$ROOT/build.py"
elif command -v python >/dev/null 2>&1; then
  python "$ROOT/build.py"
else
  echo "Error: No python interpreter found (python3 or python)." >&2
  echo "Install Python or use the platform-specific build scripts: build.bat or build.ps1" >&2
  exit 1
fi
