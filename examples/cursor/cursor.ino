/*
  Hotboards_Spilcd Library - Cursor

 NOTE: The lcd only works with 3.3v, you need to use an arduino that works 
 with that voltage. Another option is to use a level shifter

 Demonstrates the use a 16x2 LCD display.  The Hotboards_SpiLcd
 library works with all LCD displays that are compatible with the
 SP7032 driver presented on Spi Lcd board (http://www.hotboards.org).

 This sketch prints "Hello World!" to the LCD and
 uses the cursor()  and noCursor() methods to turn
 on and off the cursor.

 The circuit:
 *  BKL   -->  GND
 *  VDD   -->  3.3v
 *  GND   -->  GND
 *  SCLK  -->  CLK (ICSP conector)
 *  SI    -->  MOSI (ICSPs conector)
 *  CS    -->  D7
 *  RS    -->  D6
 *  RST   -->  D5

 Library and example ported by Diego from Hotboards and originally cretaed by
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalCursor

 */

#include <SPI.h>
#include <Hotboards_SpiLcd.h>

// initialize the library with the numbers of the interface pins
Hotboards_SpiLcd lcd( 7, 6, 5 );


void setup() {
  // the lcd library needs the spi interface to be initilized
  SPI.begin();
  // initialize internal lcd controller:
  lcd.begin();
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the cursor:
  lcd.noCursor();
  delay(500);
  // Turn on the cursor:
  lcd.cursor();
  delay(500);
}
