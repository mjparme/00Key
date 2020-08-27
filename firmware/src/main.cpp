#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans18pt7b.h>
#include "Globals.h"
#include "KeyMap.h"

const byte rowPins[] = {33, 34};
const byte colPins[] = {31, 32};
int *keyMap;

Adafruit_SSD1306 display(128, 64, &Wire2, -1);

#pragma region OLED

void setupOled()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loopOled()
{
  display.clearDisplay();
  display.setFont(&FreeSans18pt7b);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 41);
  display.print("00Key");
  display.display();
}

#pragma endregion OLED

#pragma region Keyboard

void pressKey(byte row, byte col)
{
  auto key = KeyMap::getKey(row, col);
  Keyboard.press(key);
}

void releaseKey(byte row, byte col)
{
  auto key = KeyMap::getKey(row, col);
  Keyboard.release(key);
}

#pragma endregion Keyboard

#pragma region Scanning

void setupScan()
{
  for (byte i = 0; i < COL_COUNT; i++)
  {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  for (byte i = 0; i < ROW_COUNT; i++)
  {
    pinMode(rowPins[i], OUTPUT);
  }
}

void loopScan()
{
  for (byte rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++)
  {
    byte row = rowPins[rowIndex];

    digitalWrite(row, LOW);
    delayMicroseconds(PIN_CHANGE_DELAY);

    for (byte colIndex = 0; colIndex < COL_COUNT; colIndex++)
    {
      byte col = colPins[colIndex];

      if (digitalRead(col) == LOW)
      {
        pressKey(rowIndex, colIndex);
      }
      else
      {
        releaseKey(rowIndex, colIndex);
      }
    }

    digitalWrite(row, HIGH);
  }
}

#pragma endregion Scanning

void setup()
{
  Serial.begin(115200);
  setupScan();
  setupOled();
}

void loop()
{
  loopScan();
  loopOled();
  delay(SCAN_DELAY);
}