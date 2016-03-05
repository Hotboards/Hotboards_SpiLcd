/*
  Hotboards_SpiLcd.cpp - Library for write and control and lcd with spi interfaces and the ST7032 controller.
  base on LiquidCristalDisplay library
  Created by Diego Perez, January 16, 2016.
  Released into the public domain.
*/

#ifndef Hotboards_SpiLcd_h
#define Hotboards_SpiLcd_h

#include <inttypes.h>
#include "Print.h"

// commands
#define HT_SPILCD_CLEARDISPLAY          0x01
#define HT_SPILCD_RETURNHOME            0x02
#define HT_SPILCD_ENTRYMODESET          0x04
#define HT_SPILCD_DISPLAYCONTROL        0x08
#define HT_SPILCD_CURSORSHIFT           0x10
#define HT_SPILCD_FUNCTIONSET           0x20
#define HT_SPILCD_SETCGRAMADDR          0x40
#define HT_SPILCD_SETDDRAMADDR          0x80

// flags for display entry mode
#define HT_SPILCD_ENTRYRIGHT            0x00
#define HT_SPILCD_ENTRYLEFT             0x02
#define HT_SPILCD_ENTRYSHIFTINCREMENT   0x01
#define HT_SPILCD_ENTRYSHIFTDECREMENT   0x00

// flags for display on/off control
#define HT_SPILCD_DISPLAYON             0x04
#define HT_SPILCD_DISPLAYOFF            0x00
#define HT_SPILCD_CURSORON              0x02
#define HT_SPILCD_CURSOROFF             0x00
#define HT_SPILCD_BLINKON               0x01
#define HT_SPILCD_BLINKOFF              0x00

// flags for display/cursor shift
#define HT_SPILCD_DISPLAYMOVE           0x08
#define HT_SPILCD_CURSORMOVE            0x00
#define HT_SPILCD_MOVERIGHT             0x04
#define HT_SPILCD_MOVELEFT              0x00

// flags for function set
#define HT_SPILCD_8BITMODE              0x10
#define HT_SPILCD_4BITMODE              0x00
#define HT_SPILCD_2LINE                 0x08
#define HT_SPILCD_1LINE                 0x00
#define HT_SPILCD_5x16DOTS              0x04
#define HT_SPILCD_5x8DOTS               0x00
#define HT_SPILCD_EXTINST               0x01
#define HT_SPILCD_NORMINST              0x00


/** Hotboards_SpiLcd class.
 *  Used to control lcd with spi serial interface
 *
 * Example:
 * @code
 * #include <Arduino.h>
 * #include <Hotboards_SpiLcd.h>
 *
 * Hotboards_SpiLcd lcd( 7, 6, 5 ); //cs, rs, rst
 * 
 * void setup( void ) {
 *     SPI.begin( );
 *     lcd.begin( );
 *     lcd.print( "Hola mundo" );
 * }
 * 
 * @endcode
 */
class Hotboards_SpiLcd : public Print
{
  public:
  
    /** Create Hotboards_SpiLcd instance
      * @param cs pin to control the chip select signal
      * @param rs pin to control the data/command signal
      * @param rst pin to control the reset signal
      *
      * Example:
      * @code
      *   // then we can create the instance
      *   Hotboards_SpiLcd lcd( 7, 6, 5 ); //cs, rs, rst
      * @endcode
      */
    Hotboards_SpiLcd( int cs, int rs, int rst );
    
    /** Send commands to initialize internal lcd controller
      *
      * Example:
      * @code
      *   // After create the instance we init
      *   // but we need to init the SPI first
      *   SPI.begin();
      *   lcd.begin();
      * @endcode
      */
    void begin( void );
    
    /** Clears the LCD screen and positions the cursor in the upper-left corner. 
      *
      * Example:
      * @code
      *   lcd.clear();
      * @endcode
      */
    void clear( void );
    
    /** Positions the cursor in the upper-left of the LCD. That is, use that location 
      * in outputting subsequent text to the display. To also clear the display, use 
      * the clear() function instead
      *
      * Example:
      * @code
      *   lcd.home();
      * @endcode
      */
    void home( void );

    /** Turns off the LCD display, without losing the text currently shown on it.
      *
      * Example:
      * @code
      *   lcd.noDisplay();
      * @endcode
      */
    void noDisplay( void );
    
    /** Turns on the LCD display, after it's been turned off with noDisplay(). 
      * This will restore the text (and cursor) that was on the display. 
      *
      * Example:
      * @code
      *   lcd.display();
      * @endcode
      */
    void display( void );
    
    /** Turns off the blinking LCD cursor. 
      *
      * Example:
      * @code
      *   lcd.noBlink();
      * @endcode
      */
    void noBlink( void );
    
    /** Display the blinking LCD cursor. If used in combination with the cursor() function, 
      * the result will depend on the particular display. 
      *
      * Example:
      * @code
      *   lcd.blink();
      * @endcode
      */
    void blink( void );
    
    /** Hides the LCD cursor.
      *
      * Example:
      * @code
      *   lcd.noCursor();
      * @endcode
      */
    void noCursor( void );
    
    /** Display the LCD cursor: an underscore (line) at the position to which the 
      * next character will be written. 
      *
      * Example:
      * @code
      *   lcd.cursor();
      * @endcode
      */
    void cursor( void );
    
    /** Scrolls the contents of the display (text and cursor) one space to the left. 
      *
      * Example:
      * @code
      *   lcd.scrollDisplayLeft();
      * @endcode
      */
    void scrollDisplayLeft( void );
    
    /** Scrolls the contents of the display (text and cursor) one space to the right. 
      *
      * Example:
      * @code
      *   lcd.scrollDisplayRight();
      * @endcode
      */
    void scrollDisplayRight( void );
    
    /** Set the direction for text written to the LCD to left-to-right, the default. 
      * This means that subsequent characters written to the display will go from left to right, 
      * but does not affect previously-output text. 
      *
      * Example:
      * @code
      *   lcd.leftToRight();
      * @endcode
      */
    void leftToRight( void );
    
    /** Set the direction for text written to the LCD to right-to-left (the default is left-to-right). 
      * This means that subsequent characters written to the display will go from right to left, 
      * but does not affect previously-output text. 
      *
      * Example:
      * @code
      *   lcd.rightToLeft();
      * @endcode
      */
    void rightToLeft( void );
    
    /** Turns on automatic scrolling of the LCD. This causes each character 
      * output to the display to push previous characters over by one space. 
      * If the current text direction is left-to-right (the default), 
      * the display scrolls to the left; if the current direction is right-to-left, 
      * the display scrolls to the right. This has the effect of outputting 
      * each new character to the same location on the LCD. 
      *
      * Example:
      * @code
      *   lcd.autoscroll();
      * @endcode
      */
    void autoscroll( void );
    
    /** Turns off automatic scrolling of the LCD.
      *
      * Example:
      * @code
      *   lcd.noAutoscroll();
      * @endcode
      */
    void noAutoscroll( void );

    //void setRowOffsets( int row1, int row2 );
    //void createChar( uint8_t, uint8_t[] );
    
    /** Position the LCD cursor; that is, set the location at which subsequent 
      * text written to the LCD will be displayed.
      * @param col: the column at which to position the cursor (with 0 being the first column)
      * @param row: the row at which to position the cursor (with 0 being the first row) 
      *
      * Example:
      * @code
      *   lcd.setCursor( 3, 1 );
      * @endcode
      */
    void setCursor( uint8_t, uint8_t ); 
    
    /** Send a command to the LCD.
      * @data: cmd command to send
      *
      * Example:
      * @code
      *   // clear screen command
      *   lcd.command( 0x30 );
      * @endcode
      */ 
    void command( uint8_t );
    
    virtual size_t write( uint8_t );
    
    using Print::write;
  
  private:

    void send( uint8_t, uint8_t );
    
    uint8_t _cs_pin;
    uint8_t _rs_pin;
    uint8_t _rst_pin;

    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
};

#endif /* Hotboards_SpiLcd_h */

