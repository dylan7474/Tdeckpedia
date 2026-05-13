# Tdeckpedia

Tdeckpedia is an offline, Hitchhiker's Guide-inspired Wikipedia reader for the LilyGO T-Deck (ESP32-S3). It reads preprocessed article text files from a microSD card and displays them in a retro **"DON'T PANIC"** terminal-style interface.

## What this project does

- Runs fully offline on-device (no Wi-Fi required during reading).
- Looks up article files with this path pattern:
  - `/wiki/<LETTER>/<query>.txt`
- Uses the T-Deck keyboard for text entry and Enter-based search.

## Hardware requirements

- LilyGO T-Deck (ESP32-S3)
- microSD card (64GB+ recommended for large Wikipedia datasets)
- USB cable for flashing firmware

## Repository structure

- `tdeckpedia/tdeckpedia.ino` — firmware for the T-Deck.
- `prep.py` — preprocessing script intended to convert Wikipedia source data into SD-card article files.

## Getting the Wikipedia source database

Tdeckpedia content preparation starts from a **Wikipedia ZIM archive**.

1. Go to Kiwix downloads:
   - https://download.kiwix.org/zim/wikipedia/
2. Choose a dataset variant that matches your SD card capacity and your content needs.
   - Common full-English option: `wikipedia_en_all_nopic_*.zim`
   - Smaller variants (e.g., mini/simple) may be easier to process and store.
3. Download the `.zim` file to your computer.

> Tip: Keep the exact downloaded filename; you'll use that path when running the prep script.

## Preparing SD content with `prep.py`

The ESP32-S3 cannot query raw `.zim` files directly, so you must preprocess on your computer first.

### 1) Install Python dependencies

Create/activate a virtual environment (optional but recommended), then install dependencies:

```bash
pip install libzim beautifulsoup4
```

### 2) Configure input ZIM path

Open `prep.py` and set the path variable/input it expects so it points to your downloaded Wikipedia `.zim` file.

### 3) Run preprocessing

```bash
python prep.py
```

The script should generate a `wiki/` output tree with entries similar to:

- `wiki/E/Earth.txt`
- `wiki/M/Mars.txt`

### 4) Copy output to microSD

Copy the generated `wiki/` folder to the **root** of your microSD card.

Expected card layout:

```text
/<SD root>/wiki/A/...txt
/<SD root>/wiki/B/...txt
...
```

## Flashing the firmware

1. Open `tdeckpedia/tdeckpedia.ino` in Arduino IDE.
2. Install required libraries:
   - `TFT_eSPI`
   - Built-in: `SPI`, `SD`, `Wire`
3. Select an ESP32-S3-compatible board profile (commonly `ESP32S3 Dev Module`).
4. Use board settings that match your T-Deck setup.
5. Flash firmware and insert the prepared SD card.

## Controls

- **Type**: Enter query text with the keyboard.
- **Backspace**: Delete the previous character.
- **Enter**: Search the local archive.
- **Missing article**: Device shows an `ENTRY NOT FOUND` message.

## Notes and troubleshooting

- If you get SD card errors, verify FAT-compatible formatting and card seating.
- If no articles are found, confirm filename/path conventions match the firmware lookup format exactly.
- Start with a smaller ZIM variant if full English processing is too slow or too large for your storage.

## License and credits

- Inspired by *The Hitchhiker's Guide to the Galaxy*.
- Wikipedia content licensing is governed by Wikipedia/its publishers (commonly CC BY-SA, depending on source package).
- Project license: see `LICENSE`.
