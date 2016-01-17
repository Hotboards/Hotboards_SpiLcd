
/*
  LiquidCrystal Library - scrollDisplayLeft() and scrollDisplayRight()

 NOTE: The lcd only works with 3.3v, you need to use an arduino that works 
 with that voltage. another option is to use a level shifter

 Demonstrates the use a 16x2 LCD display.  The Hotboards_SpiLcd
 library works with all LCD displays that are compatible with the
 SP7032 driver presented on Spi Lcd board (http://www.hotboards.org).

 This sketch prints "Hello World!" to the LCD and uses the
 scrollDisplayLeft() and scrollDisplayRight() methods to scroll
 the text.

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


void setup() {
  // the lcd library needs the spi interface to be initilized
  SPI.begin();
  // initialize internal lcd controller:
  lcd.begin();
  // print a welcome message
  lcd.print("Helo world");
  // hold the message by one second
  delay(1000);
}

void loop() {
  // scroll 13 positions (string length) to the left
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // delay at the end of the full loop:
  delay(1000);
}


