# Tdeckpedia

Tdeckpedia is an offline, Hitchhiker's Guide-inspired article browser for the LilyGO T-Deck. It runs on the ESP32-S3, reads article text files from a microSD card, and renders results on the built-in 320x240 display with a retro "DON'T PANIC" style interface.

## What the application is

- A standalone firmware app for the LilyGO T-Deck.
- A local archive reader that looks up files using the pattern `/wiki/<LETTER>/<query>.txt`.
- A keyboard-driven interface for quick text search of preprocessed content on SD storage.

## Build and flash instructions

1. Open `tdeckpedia/tdeckpedia.ino` in Arduino IDE (or PlatformIO with equivalent board config).
2. Install required libraries:
   - `TFT_eSPI`
   - Built-in Arduino libraries: `SPI`, `SD`, `Wire`
3. Use board settings compatible with T-Deck ESP32-S3 (for example, `ESP32S3 Dev Module`).
4. Flash the firmware to the T-Deck.
5. Insert an SD card containing a `wiki` folder produced by `prep.py`.

## Basic controls

- **Type**: Use the T-Deck keyboard to enter a search query.
- **Backspace**: Deletes the last character.
- **Enter**: Executes a search and displays the matching article if present.
- **No result**: Shows an "ENTRY NOT FOUND" message when the expected text file is missing.

## Roadmap

- Add paging/scroll controls for long articles.
- Add a "home" or "clear results" action without restarting.
- Add case-insensitive and alias-aware lookup improvements.
- Improve preprocessing docs and add sample data layout validation.

## Project structure

- `tdeckpedia/tdeckpedia.ino` – firmware source.
- `prep.py` – preprocessing helper for creating SD-compatible archive files.
