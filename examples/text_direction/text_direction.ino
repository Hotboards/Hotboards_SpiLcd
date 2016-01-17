/*
Hotboards_SpiLcd - TextDirection

 NOTE: The lcd only works with 3.3v, you need to use an arduino that works 
 with that voltage. Another option is to use a level shifter

 Demonstrates the use a 16x2 LCD display.  The Hotboards_SpiLcd
 library works with all LCD displays that are compatible with the
 SP7032 driver presented on Spi Lcd board (http://www.hotboards.org).

This sketch demonstrates how to use leftToRight() and rightToLeft()
to move the cursor.

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

*/

#include <SPI.h>
#include <Hotboards_SpiLcd.h>

// initialize the library with the numbers of the interface pins
Hotboards_SpiLcd lcd( 7, 6, 5 );

int thisChar = 'a';

void setup() {
  // the lcd library needs the spi interface to be initilized
  SPI.begin();
  // initialize internal lcd controller:
  lcd.begin();
  // turn on the cursor:
  lcd.cursor();
}

void loop() {
  // reverse directions at 'm':
  if (thisChar == 'm') {
    // go right for the next letter
    lcd.rightToLeft();
  }
  // reverse again at 's':
  if (thisChar == 's') {
    // go left for the next letter
    lcd.leftToRight();
  }
  // reset at 'z':
  if (thisChar > 'z') {
    // go to (0,0):
    lcd.home();
    // start again at 0
    thisChar = 'a';
  }
  // print the character
  lcd.write(thisChar);
  // wait a second:
  delay(1000);
  // increment the letter:
  thisChar++;
}
