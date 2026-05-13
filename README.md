Tdeckpedia: The Hitchhiker's Guide (T-Deck Edition)

"A towel, it says, is about the most massively useful thing an interstellar hitchhiker can have."

Tdeckpedia is a standalone, offline Wikipedia reader designed for the LilyGO T-Deck. Inspired by The Hitchhiker's Guide to the Galaxy, this project transforms your T-Deck into a portable encyclopedia that requires zero internet connection, pulling data directly from a highly compressed local archive on a MicroSD card.

🌌 Features

100% Offline: Access the sum of human knowledge (Wikipedia) in the palm of your hand without Wi-Fi or Cellular data.

Authentic Aesthetics: Vector-style green text on a black background, complete with the iconic "DON'T PANIC" boot screen.

Hardware Optimized: Leverages the T-Deck's built-in keyboard, 320x240 ST7789 display, and ESP32-S3 processor.

Procedural Display: Text renders with a slight "typing" delay to simulate the classic Guide interface.

🛠️ Hardware Requirements

LilyGO T-Deck (ESP32-S3 with integrated keyboard and trackball).

MicroSD Card: 64GB or larger (Class 10/U1 recommended).

Data Source: A Wikipedia .zim file (e.g., the wikipedia_en_all_nopic archive from Kiwix).

🚀 Getting Started

1. Prepare the Wikipedia Data

The ESP32 cannot parse massive .zim files directly. You must first use the provided Python script to extract and index the articles on your PC.

Install Python Dependencies:

pip install libzim beautifulsoup4


Configure prep_wiki.py:
Open prep_wiki.py and set the ZIM_FILE_PATH to your downloaded .zim file.

Run the script:

python prep_wiki.py


This will create a wiki folder organized alphabetically (e.g., /wiki/E/Earth.txt).

Transfer to SD: Copy the wiki folder to the root of your MicroSD card.

2. Flash the Firmware

Open tdeckpedia/tdeckpedia.ino in the Arduino IDE.

Install Required Libraries:

TFT_eSPI (Configure User_Setup.h for the T-Deck or use the LilyGO T-Deck library).

SPI, SD, Wire (Standard).

Board Settings:

Board: ESP32S3 Dev Module

USB CDC On Boot: Enabled

Flash Mode: QIO 80MHz

Partition Scheme: 16M Flash (3MB APP/9.9MB FATFS)

Upload to your T-Deck.

🎮 Controls

Boot: Upon powering on, the "DON'T PANIC" screen will appear.

Typing: Use the physical keyboard to type your query.

Search: Press ENTER to query the Sub-Etha archives.

Backspace: Correct typing errors.

Clear: (Coming Soon) Use the trackball click to return to the home screen.

📁 Directory Structure

/tdeckpedia/: The Arduino source code for the ESP32-S3.

/prep_wiki.py: Python utility to convert Kiwix ZIM files into T-Deck compatible text files.

📜 License & Credits

Inspired by Douglas Adams' The Hitchhiker's Guide to the Galaxy.

Original Web/Pi project by dylan7474.

Wikipedia content provided by Wikipedia under CC BY-SA 3.0.

Share and Enjoy.
