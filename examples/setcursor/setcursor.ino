/*
  Hotboards_SpiLcd Library - setCursor

 NOTE: The lcd only works with 3.3v, you need to use an arduino that works 
 with that voltage. Another option is to use a level shifter

 Demonstrates the use a 16x2 LCD display.  The Hotboards_SpiLcd
 library works with all LCD displays that are compatible with the
 SP7032 driver presented on Spi Lcd board (http://www.hotboards.org).

 This sketch prints to all the positions of the LCD using the
 setCursor() method:

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
}

void loop() {
  // loop from ASCII 'a' to ASCII 'z':
  for (int thisLetter = 'a'; thisLetter <= 'z'; thisLetter++) 
  {
    // loop over the columns:
    for (int  thisRow = 0; thisRow < 2; thisRow++) 
    {
      // loop over the rows:
      for (int thisCol = 0; thisCol < 16; thisCol++) 
      {
        // set the cursor position:
        lcd.setCursor(thisCol, thisRow);
        // print the letter:
        lcd.write(thisLetter);
        delay(200);
      }
    }
  }
}
