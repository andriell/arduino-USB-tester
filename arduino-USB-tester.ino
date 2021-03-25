#include "config.h"
#include <SD.h>
#include <SPI.h>

// SSD1306Ascii
//#include "SSD1306Ascii.h"
//#include "SSD1306AsciiAvrI2c.h"

#include "U8glib.h" // U8glib

#define MAX_UL     0xFFFFFFFFUL

unsigned long executionTime;

void setup() {
  Serial.begin(9600);
  ledSetup();
  ledBlink(3, 50);
  adcSetup();
  displaySetup();
  sdSetup();
}

void loop() {
  unsigned long startMillis = millis();
  Serial.print("Execution time: ");
  Serial.println(executionTime);

  adcLoop();
  displayLoop();
  sdLoop();

  unsigned long endMillis = millis();
  if (endMillis < startMillis) {
    executionTime = MAX_UL - startMillis;
    executionTime += endMillis + 1;
  } else {
    executionTime = endMillis - startMillis;
  }
  if (executionTime < 1000UL) {
    delay(1000UL - executionTime);
  }

}
