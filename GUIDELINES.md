# GUIDELINES.md

Behavioral guidelines to reduce common LLM coding mistakes. Merge with project-specific instructions as needed.

**Tradeoff:** These guidelines bias toward caution over speed. For trivial tasks, use judgment.

## 1. Think Before Coding

**Don't assume. Don't hide confusion. Surface tradeoffs.**

Before implementing:
- State your assumptions explicitly. If uncertain, ask.
- If multiple interpretations exist, present them - don't pick silently.
- If a simpler approach exists, say so. Push back when warranted.
- If something is unclear, stop. Name what's confusing. Ask.

## 2. Simplicity First

**Minimum code that solves the problem. Nothing speculative.**

- No features beyond what was asked.
- No abstractions for single-use code.
- No "flexibility" or "configurability" that wasn't requested.
- No error handling for impossible scenarios.
- If you write 200 lines and it could be 50, rewrite it.

Ask yourself: "Would a senior engineer say this is overcomplicated?" If yes, simplify.

## 3. Surgical Changes

**Touch only what you must. Clean up only your own mess.**

When editing existing code:
- Don't "improve" adjacent code, comments, or formatting.
- Don't refactor things that aren't broken.
- Match existing style, even if you'd do it differently.
- If you notice unrelated dead code, mention it - don't delete it.

When your changes create orphans:
- Remove imports/variables/functions that YOUR changes made unused.
- Don't remove pre-existing dead code unless asked.

The test: Every changed line should trace directly to the user's request.

## 4. Goal-Driven Execution

**Define success criteria. Loop until verified.**

Transform tasks into verifiable goals:
- "Add validation" → "Write tests for invalid inputs, then make them pass"
- "Fix the bug" → "Write a test that reproduces it, then make it pass"
- "Refactor X" → "Ensure tests pass before and after"

For multi-step tasks, state a brief plan:
```
1. [Step] → verify: [check]
2. [Step] → verify: [check]
3. [Step] → verify: [check]
```

Strong success criteria let you loop independently. Weak criteria ("make it work") require constant clarification.

---

## 5. Building & Running with build.py

**Cross-platform build launcher for convenience and consistency.**

The project includes `build.py`, a Python 3 script that provides a unified interface for building and running across Windows, macOS, and Linux. Use it instead of platform-specific commands.

### Usage

```bash
python3 build.py [action]
```

### Actions

- **`build`** (default) – compile the project and output binary to `bin/`
  ```bash
  python3 build.py build
  # or simply:
  python3 build.py
  ```

- **`run`** – execute the existing binary (must build first)
  ```bash
  python3 build.py run
  ```

- **`build_run`** – compile and immediately execute
  ```bash
  python3 build.py build_run
  ```

### How It Works

- **macOS/Linux:** automatically detects and uses `make` (preferred) or falls back to `scripts/build_project.sh`.
- **Windows:** uses PowerShell `build.ps1` (preferred) or `build.bat`, with automatic WSL/Git Bash fallback.
- Auto-detects source directory, app name, and include paths from your project structure.
- Binary output location: `bin/<app_name>` (or `.exe` on Windows).

### Examples

```bash
# Build only
python3 build.py

# Build and run immediately
python3 build.py build_run

# Run previous build without rebuilding
python3 build.py run
```

---

**These guidelines are working if:** fewer unnecessary changes in diffs, fewer rewrites due to overcomplication, and clarifying questions come before implementation rather than after mistakes.