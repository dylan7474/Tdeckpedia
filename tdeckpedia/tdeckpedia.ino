#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <Wire.h>

/* * HITCHHIKER'S GUIDE TO THE GALAXY - T-DECK EDITION
 * Stripped AI version: Local SD Archive Reader
 */

// T-Deck Pins
#define SD_CS          39
#define BOARD_POWERON  10
#define KB_INT         46

// Colors (Matching the web version aesthetics)
#define GUIDE_GREEN    0x07E0
#define GUIDE_AMBER    0xFBE0
#define GUIDE_BLACK    0x0000

TFT_eSPI tft = TFT_eSPI();
String currentQuery = "";
bool inSearchMode = false;

// Display constants
const int headerHeight = 25;
const int margin = 10;

void drawHeader(String title) {
  tft.fillRect(0, 0, 320, headerHeight, GUIDE_GREEN);
  tft.setTextColor(GUIDE_BLACK);
  tft.setTextSize(2);
  tft.drawString("GUIDE", 5, 5);
  
  tft.setTextSize(1);
  tft.drawRightString(title, 315, 8, 2);
}

void showBootScreen() {
  tft.fillScreen(GUIDE_BLACK);
  tft.setTextColor(GUIDE_AMBER);
  tft.setTextSize(4);
  tft.drawCentreString("DON'T PANIC", 160, 100, 1);
  
  tft.setTextColor(GUIDE_GREEN);
  tft.setTextSize(1);
  tft.drawCentreString("V1.0 - SUB-ETHA OFFLINE", 160, 150, 2);
}

void searchArchive(String query) {
  query.trim();
  if (query.length() == 0) return;

  tft.fillScreen(GUIDE_BLACK);
  drawHeader("SEARCHING...");
  
  // File Path Construction: /wiki/E/EARTH.TXT
  String firstChar = query.substring(0, 1);
  firstChar.toUpperCase();
  String filename = "/wiki/" + firstChar + "/" + query + ".txt";
  
  if (!SD.exists(filename)) {
    tft.setCursor(margin, headerHeight + margin);
    tft.setTextColor(GUIDE_GREEN);
    tft.println("ENTRY NOT FOUND: " + query);
    tft.println("\nThe Guide searched the local archives but found no probabilities.");
    return;
  }

  File entry = SD.open(filename);
  drawHeader(query.toUpperCase());
  tft.setCursor(margin, headerHeight + margin);
  tft.setTextColor(GUIDE_GREEN);
  tft.setTextSize(1);
  
  while (entry.available()) {
    char c = entry.read();
    tft.print(c);
    // Simple delay for "computer typing" feel
    if (c != ' ') delay(5); 
  }
  entry.close();
}

void updateInputDisplay() {
  tft.fillRect(0, 210, 320, 30, 0x1082); // Darker grey for input bar
  tft.drawRect(0, 210, 320, 30, GUIDE_GREEN);
  tft.setTextColor(GUIDE_GREEN);
  tft.setCursor(10, 220);
  tft.print("> " + currentQuery + "_");
}

void setup() {
  Serial.begin(115200);
  
  // Power on the T-Deck peripherals
  pinMode(BOARD_POWERON, OUTPUT);
  digitalWrite(BOARD_POWERON, HIGH);
  
  // Initialize Display
  tft.init();
  tft.setRotation(1);
  showBootScreen();

  // Initialize SD
  SPI.begin(18, 19, 21, SD_CS);
  if (!SD.begin(SD_CS)) {
    tft.setTextColor(0xF800); // Red
    tft.drawCentreString("SD CARD ERROR", 160, 200, 2);
  }

  // Initialize Keyboard (assuming standard I2C keyboard on T-Deck)
  Wire.begin(10, 11); 

  delay(2000);
  tft.fillScreen(GUIDE_BLACK);
  drawHeader("READY");
  updateInputDisplay();
}

void loop() {
  // T-Deck Keyboard Handling
  // Note: Most T-Deck versions use an I2C Keyboard (address 0x55)
  Wire.requestFrom(0x55, 1);
  if (Wire.available()) {
    char key = Wire.read();
    if (key != 0) {
      if (key == 8) { // Backspace
        if (currentQuery.length() > 0) {
          currentQuery.remove(currentQuery.length() - 1);
        }
      } else if (key == 13) { // Enter
        searchArchive(currentQuery);
        currentQuery = "";
      } else if (currentQuery.length() < 30) {
        currentQuery += key;
      }
      updateInputDisplay();
    }
  }
  delay(10);
}
