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


def detect_source_directory() -> str:
    """Scan workspace for C++ source files.

    Returns a relative directory path containing the largest number of
    *.cpp files. If the root contains the most, returns '.'.
    """
    counters: dict[str,int] = {}
    for dirpath, dirnames, filenames in os.walk(ROOT):
        # ignore hidden and support directories
        if any(part.startswith('.') for part in os.path.relpath(dirpath, ROOT).split(os.sep)):
            continue
        for fn in filenames:
            if fn.endswith('.cpp') or fn.endswith('.cc') or fn.endswith('.cxx'):
                rel = os.path.relpath(dirpath, ROOT)
                counters[rel] = counters.get(rel, 0) + 1
    if not counters:
        return '.'
    # choose directory with max count
    best = max(counters, key=counters.get)
    return best


def detect_app_name() -> str:
    """Try to determine a sensible application name.

    Strategy:
    1. If the detected source directory is '<appname>/src' (or similar), use
       '<appname>' — this is the most reliable signal in this project layout.
    2. Look for a top-level subdirectory that contains both 'src/' and 'include/'
       siblings, which indicates a self-contained app folder.
    3. Fall back to the name of the repository root directory.

    Note: we intentionally do NOT derive the name from whichever .cpp file
    happens to contain 'int main' first, because test files and demo files also
    define main() and would produce wrong names (e.g. 'combat_test' or
    'pointers_demo') depending on filesystem walk order.
    """
    srcdir = detect_source_directory()
    parts = srcdir.replace('/', os.sep).split(os.sep)
    # Pattern: '<appname>/src' → return '<appname>'
    if len(parts) >= 2 and parts[-1] in ('src', 'source', 'sources'):
        return parts[-2]
    # Pattern: look for a top-level dir that owns both src/ and include/
    try:
        entries = os.listdir(ROOT)
    except OSError:
        entries = []
    for entry in sorted(entries):
        full = os.path.join(ROOT, entry)
        if os.path.isdir(full):
            if (os.path.isdir(os.path.join(full, 'src')) and
                    os.path.isdir(os.path.join(full, 'include'))):
                return entry
    # fallback to root directory name
    return os.path.basename(ROOT)


def detect_include_directory() -> str:
    """Scan workspace for header files and return the directory containing the most.

    If no headers are found, return '.'.
    If the detected directory ends with the application name (e.g.
    "dungeongame/include/dungeongame"), strip that last component and return the
    parent ("dungeongame/include") so that the Makefile can still append the
    app-specific subdirectory for -I flags.
    """
    counters: dict[str,int] = {}
    for dirpath, dirnames, filenames in os.walk(ROOT):
        # skip hidden folders
        if any(part.startswith('.') for part in os.path.relpath(dirpath, ROOT).split(os.sep)):
            continue
        for fn in filenames:
            if fn.endswith(('.h', '.hpp', '.hh')):
                rel = os.path.relpath(dirpath, ROOT)
                counters[rel] = counters.get(rel, 0) + 1
    if not counters:
        return '.'
    best = max(counters, key=counters.get)
    # if best is a subdirectory of an "include" folder, return that include folder
    parts = best.split(os.sep)
    if 'include' in parts:
        idx = parts.index('include')
        return os.path.join(*parts[:idx+1])
    # if best ends with APP, return its parent directory
    appname = detect_app_name()
    if best.endswith(os.sep + appname):
        return os.path.dirname(best)
    return best


def build_posix(run_after: bool = False):
    # Prefer make
    if shutil.which('make'):
        srdir = detect_source_directory()
        appname = detect_app_name()
        incdir = detect_include_directory()
        print(f"Detected source directory '{srdir}', app name '{appname}', include dir '{incdir}'")
        cmd = ['make', f'SRCDIR={srdir}', f'APP={appname}', f'INCDIR={incdir}']
        if run_after:
            cmd.append('RUN_ON_BUILD=1')
        run(cmd, cwd=ROOT)
        return
    # Fallback to shell script
    script = os.path.join(ROOT, 'scripts', 'build_project.sh')
    if os.path.isfile(script):
        run(['bash', script], cwd=ROOT)
        return
    print('Error: No build method found on POSIX platform. Install make or ensure scripts/build_project.sh exists.', file=sys.stderr)
    sys.exit(2)


def build_windows(run_after: bool = False):
    # Prefer PowerShell script
    ps_script = os.path.join(ROOT, 'build.ps1')
    bat_script = os.path.join(ROOT, 'build.bat')
    srdir = detect_source_directory()
    appname = detect_app_name()
    incdir = detect_include_directory()
    if os.path.isfile(ps_script) and shutil.which('powershell'):
        # pass parameters as arguments
        args = ['powershell', '-ExecutionPolicy', 'Bypass', '-File', ps_script,
             '-SRCDIR', srdir, '-APP', appname, '-INCDIR', incdir]
        if run_after:
            args.extend(['-Run','1'])
        run(args, cwd=ROOT)
        return
    if os.path.isfile(bat_script):
        # Run via cmd.exe, set environment variables for the call
        envcmd = f'SET SRCDIR={srdir} && SET APP={appname} && SET INCDIR={incdir}'
        if run_after:
            envcmd += ' && SET RUN_ON_BUILD=1'
        cmd = ['cmd', '/c', envcmd + f' && {bat_script}']
        run(cmd, cwd=ROOT)
        return
    # If using WSL or Git Bash, fall back to POSIX build
    if shutil.which('bash'):
        build_posix()
        return
    print('Error: No suitable Windows build script found. Ensure build.ps1 or build.bat is present or use WSL/Git Bash.', file=sys.stderr)
    sys.exit(3)


def main():
    import argparse

    parser = argparse.ArgumentParser(description='Cross-platform build launcher')
    parser.add_argument('action', nargs='?', choices=['build', 'run', 'build_run'],
                        default='build', help='what to do (default: build)')
    args = parser.parse_args()

    print('Cross-platform build launcher starting...')

    # determine app name up front so run-only mode works even if build is skipped
    appname = detect_app_name()
    binary = os.path.join('bin', appname + ('.exe' if sys.platform == 'win32' else ''))

    if args.action == 'run':
        print(f'Running existing binary: {binary}')
        if os.path.isfile(binary):
            run([binary])
        else:
            print('Error: binary not found, please build first.', file=sys.stderr)
            sys.exit(1)
        return

    # if we reach here we either need to build or build+run
    # build with optional run flag support
    platform = sys.platform
    if platform == 'win32':
        build_windows(run_after=(args.action == 'build_run'))
    else:
        build_posix(run_after=(args.action == 'build_run'))

    print('Build finished successfully.')


if __name__ == '__main__':
    main()
