# AGENTS.md

Guidance for AI coding agents working in this repository.

## Project overview

- `tdeckpedia/tdeckpedia.ino` contains the device firmware for LilyGO T-Deck.
- `prep.py` prepares content archives for SD card usage.
- The firmware expects article files at `/wiki/<LETTER>/<query>.txt`.

## Development notes

- Keep hardware-specific pin definitions explicit and documented.
- Prefer small, testable helper functions over large inline logic blocks.
- Preserve the retro UI tone (`DON'T PANIC`, GUIDE color scheme) unless asked to redesign.

## Documentation standards

- When changing controls or UX behavior, update `README.md` in the same change.
- Keep setup instructions focused on minimum working steps.
- Avoid speculative dependencies; list only what the repo actually uses.

## Agent workflow

- Before edits, scan for nested `AGENTS.md` files in affected directories.
- After edits, run lightweight checks (format/lint if available) and summarize results.
- Keep commits scoped and descriptive.
