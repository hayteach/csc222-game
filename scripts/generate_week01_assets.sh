#!/usr/bin/env bash
set -euo pipefail

# Generates PDF handout and slides if pandoc is available
HANDOUT_MD="week01/handout.md"
SLIDES_MD="week01/slides.md"
HANDOUT_PDF="week01/handout.pdf"
SLIDES_PDF="week01/slides.pdf"

if ! command -v pandoc >/dev/null 2>&1; then
  echo "Pandoc not found. Install pandoc to generate PDFs: https://pandoc.org/"
  exit 0
fi

# Generate handout
pandoc "$HANDOUT_MD" -o "$HANDOUT_PDF" --pdf-engine=pdflatex
# Generate slides (simple reveal.js style if desired)
pandoc "$SLIDES_MD" -o "$SLIDES_PDF" --pdf-engine=pdflatex

echo "Generated: $HANDOUT_PDF and $SLIDES_PDF"
