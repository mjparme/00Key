#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include "OLED.h"

Adafruit_SSD1306 display(128, 64, &Wire2, -1);
int _layer = 0;
int _blPercentage = 0;
bool _capsOn = false;

int _rValue = 128;
int _gValue = 0;
int _bValue = 255;

bool _splashScreenFinished = false;
int _splashScreenDuration = 3000;

// clang-format off

const unsigned char _logo[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x60, 
	0x03, 0xe0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xc0, 
	0x01, 0x1e, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x40, 0x78, 0x80, 
	0x00, 0x85, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xa1, 0x00, 
	0x00, 0x68, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0x16, 0x00, 
	0x00, 0x10, 0x40, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x02, 0x08, 0x00, 
	0x00, 0x10, 0x40, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x02, 0x08, 0x00, 
	0x00, 0x08, 0x21, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x01, 0x84, 0x10, 0x00, 
	0x00, 0x04, 0x16, 0x60, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x06, 0x68, 0x20, 0x00, 
	0x0f, 0xe4, 0x19, 0x18, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x18, 0x98, 0x27, 0xf0, 
	0x12, 0x1e, 0x21, 0x06, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x60, 0x84, 0x78, 0x48, 
	0x11, 0x01, 0x40, 0xf9, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x9f, 0x02, 0x80, 0x88, 
	0x20, 0x80, 0x81, 0x06, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x60, 0x81, 0x01, 0x04, 
	0x43, 0xc0, 0x82, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x41, 0x03, 0xc2, 
	0x8c, 0x3c, 0x4d, 0x00, 0x1f, 0x83, 0xf0, 0x79, 0xf3, 0x80, 0x9f, 0x38, 0x00, 0xb2, 0x3c, 0x31, 
	0xb0, 0x43, 0xd0, 0x80, 0x3f, 0x83, 0xf0, 0x79, 0xe3, 0x80, 0x9f, 0x3c, 0x01, 0x0b, 0xc2, 0x0d, 
	0xc0, 0x41, 0x60, 0x60, 0x3e, 0x78, 0xcf, 0x19, 0xc6, 0x7f, 0x9f, 0x3c, 0x06, 0x06, 0x82, 0x03, 
	0x00, 0x86, 0x30, 0x10, 0x3e, 0x78, 0xcf, 0x19, 0x8e, 0x7f, 0x9f, 0x3c, 0x08, 0x0c, 0x61, 0x00, 
	0x00, 0x9a, 0x2c, 0x28, 0x3e, 0x74, 0xce, 0x99, 0x1e, 0x7f, 0x9f, 0x3c, 0x14, 0x34, 0x59, 0x00, 
	0x01, 0x64, 0x22, 0x28, 0x7e, 0x74, 0xce, 0x98, 0x3e, 0x7f, 0x9f, 0x3e, 0x14, 0x44, 0x26, 0x80, 
	0x01, 0x84, 0x21, 0x48, 0x7e, 0x6c, 0xcd, 0x98, 0x7e, 0x07, 0xe0, 0x3e, 0x12, 0x84, 0x21, 0x80, 
	0x02, 0x08, 0x40, 0x88, 0x7e, 0x6c, 0xcd, 0x98, 0x7e, 0x07, 0xe0, 0x3e, 0x11, 0x02, 0x10, 0x40, 
	0x00, 0x08, 0x40, 0x48, 0x7e, 0x5c, 0xcb, 0x98, 0x3e, 0x7f, 0xff, 0x3e, 0x12, 0x02, 0x10, 0x00, 
	0x00, 0x08, 0x40, 0x48, 0x7e, 0x5c, 0xcb, 0x99, 0x1e, 0x7f, 0xff, 0x3e, 0x12, 0x02, 0x10, 0x00, 
	0x00, 0x08, 0x40, 0x28, 0x7e, 0x3c, 0xc7, 0x99, 0x8e, 0x7f, 0x9f, 0x3e, 0x14, 0x02, 0x10, 0x00, 
	0x00, 0x10, 0x40, 0x18, 0x7e, 0x3c, 0xc7, 0x99, 0xc6, 0x7f, 0x9f, 0x3e, 0x18, 0x02, 0x08, 0x00, 
	0x00, 0x10, 0x42, 0x18, 0x7f, 0x83, 0xf0, 0x79, 0xe3, 0x80, 0xe0, 0xfe, 0x18, 0x02, 0x08, 0x10, 
	0x00, 0x10, 0x80, 0x08, 0x7f, 0x83, 0xf0, 0x79, 0xf3, 0x80, 0xe0, 0xfe, 0x10, 0x01, 0x08, 0x38, 
	0x00, 0x10, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x01, 0x08, 0x10, 
	0x00, 0x10, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0x08, 0x00, 
	0x00, 0x11, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0x88, 0x00, 
	0x00, 0x22, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0x44, 0x00, 
	0x00, 0x22, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x44, 0x00, 
	0x10, 0x24, 0x40, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x02, 0x24, 0x00, 
	0x00, 0x24, 0x20, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x04, 0x04, 0x24, 0x00, 
	0x00, 0x28, 0x20, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x04, 0x14, 0x00, 
	0x00, 0x28, 0x10, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x08, 0x14, 0x00, 
	0x00, 0x38, 0x10, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x08, 0x1c, 0x00, 
	0x00, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x00, 
	0x00, 0x12, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x48, 0x00, 
	0x00, 0x11, 0x04, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x20, 0x88, 0x00, 
	0x00, 0x10, 0x84, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x21, 0x08, 0x00, 
	0x00, 0x10, 0x42, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x42, 0x08, 0x00, 
	0x00, 0x10, 0x22, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x44, 0x08, 0x00, 
	0x00, 0x08, 0x21, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x84, 0x10, 0x00, 
	0x00, 0x08, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x10, 0x00, 
	0x00, 0xe8, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x17, 0x00, 
	0x01, 0x3e, 0x04, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x01, 0x20, 0x7c, 0x80, 
	0x02, 0x0d, 0xe2, 0x40, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x02, 0x47, 0xb0, 0x40, 
	0x04, 0x02, 0x1f, 0x40, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x02, 0xf8, 0x40, 0x20, 
	0x08, 0x01, 0x81, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x10, 
	0x10, 0x00, 0x60, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x06, 0x00, 0x08, 
	0x20, 0x00, 0x10, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x08, 0x00, 0x04, 
	0x40, 0x00, 0x0c, 0x00, 0x3c, 0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x3c, 0x00, 0x30, 0x00, 0x02, 
	0x80, 0x00, 0x03, 0x00, 0x03, 0xc0, 0x00, 0x1f, 0xf8, 0x00, 0x03, 0xc0, 0x00, 0xc0, 0x00, 0x01, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x01, 0x00, 0x00, 0x00
};

// clang-format on

void draw()
{
	if (!_splashScreenFinished)
	{
		return;
	}

	display.clearDisplay();

	//Logo
	display.setFont(&FreeSansBold9pt7b);
	display.setCursor(25, 12);
	display.print("00Key v1");

	//Layer and box
	display.setFont(&FreeSans9pt7b);
	display.setCursor(3, 36);
	display.print("L: ");
	display.print(_layer);
	display.drawRect(0, 20, 36, 22, WHITE);

	//Backlight and box
	display.setCursor(39, 36);
	display.print("B: ");
	display.printf("%03d", _blPercentage);
	display.drawRect(35, 20, 60, 22, WHITE);

	//CapsLock and box
	display.drawRect(94, 20, 34, 22, WHITE);
	if (_capsOn)
	{
		display.setCursor(105, 36);
		display.print("A");
		display.drawRect(102, 22, 18, 17, WHITE);
	}
	else
	{
		display.setCursor(106, 35);
		display.print("a");
	}

	//Red value and box
	display.drawRect(0, 41, 43, 22, WHITE);
	display.setCursor(6, 58);
	display.printf("%03d", _rValue);

	//Green value and box
	display.drawRect(42, 41, 44, 22, WHITE);
	display.setCursor(49, 58);
	display.printf("%03d", _gValue);

	//Blue value and box
	display.drawRect(85, 41, 43, 22, WHITE);
	display.setCursor(91, 58);
	display.printf("%03d", _bValue);

	display.display();
}

void clearSplashScreen()
{
	_splashScreenFinished = true;
	draw();
}

void drawSplashScreen()
{
	display.drawBitmap(0, 0, _logo, 128, 64, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
	display.display();
}

void OLED::setup()
{
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.setTextSize(1);

	display.setTextColor(WHITE);
	display.setTextWrap(false);
	setLayer(0);

	drawSplashScreen();
}

void OLED::loop()
{
	if (!_splashScreenFinished && millis() > _splashScreenDuration)
	{
		clearSplashScreen();
	}
}

void OLED::setLayer(int layer)
{
	_layer = layer;
	draw();
}

void OLED::setBacklight(int percentage)
{
	_blPercentage = percentage;
	draw();
}

void OLED::toggleCaps()
{
	_capsOn = !_capsOn;
	draw();
}