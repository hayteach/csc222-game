#!/usr/bin/env python3
"""
Cross-platform build launcher for the course project.
- On POSIX (macOS/Linux): prefers `make`, falls back to `./scripts/build_project.sh`.
- On Windows: prefers PowerShell `build.ps1` (ExecutionPolicy Bypass), falls back to `build.bat`.
This script prints clear instructions when a required tool is not found.
"""

from __future__ import annotations
import os
import shutil
import subprocess
import sys

ROOT = os.path.abspath(os.path.dirname(__file__))

def run(cmd, **kwargs):
    print(f"Running: {' '.join(cmd)}")
    res = subprocess.run(cmd, **kwargs)
    if res.returncode != 0:
        sys.exit(res.returncode)


def build_posix():
    # Prefer make
    if shutil.which('make'):
        run(['make'], cwd=ROOT)
        return
    # Fallback to shell script
    script = os.path.join(ROOT, 'scripts', 'build_project.sh')
    if os.path.isfile(script):
        run(['bash', script], cwd=ROOT)
        return
    print('Error: No build method found on POSIX platform. Install make or ensure scripts/build_project.sh exists.', file=sys.stderr)
    sys.exit(2)


def build_windows():
    # Prefer PowerShell script
    ps_script = os.path.join(ROOT, 'build.ps1')
    bat_script = os.path.join(ROOT, 'build.bat')
    if os.path.isfile(ps_script) and shutil.which('powershell'):
        run(['powershell', '-ExecutionPolicy', 'Bypass', '-File', ps_script], cwd=ROOT)
        return
    if os.path.isfile(bat_script):
        # Run via cmd.exe
        run(['cmd', '/c', bat_script], cwd=ROOT)
        return
    # If using WSL or Git Bash, fall back to POSIX build
    if shutil.which('bash'):
        build_posix()
        return
    print('Error: No suitable Windows build script found. Ensure build.ps1 or build.bat is present or use WSL/Git Bash.', file=sys.stderr)
    sys.exit(3)


def main():
    print('Cross-platform build launcher starting...')
    platform = sys.platform
    if platform == 'win32':
        build_windows()
    else:
        build_posix()
    print('Build finished successfully.')


if __name__ == '__main__':
    main()
