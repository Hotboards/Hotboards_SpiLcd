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


class Hotboards_SpiLcd : public Print
{
  public:
  
    Hotboards_SpiLcd( int cs, int rs, int rst );
    void begin( void );
    void clear( void );
    void home( void );

    void noDisplay( void );
    void display( void );
    void noBlink( void );
    void blink( void );
    void noCursor( void );
    void cursor( void );
    void scrollDisplayLeft( void );
    void scrollDisplayRight( void );
    void leftToRight( void );
    void rightToLeft( void );
    void autoscroll( void );
    void noAutoscroll( void );

    //void setRowOffsets( int row1, int row2 );
    //void createChar( uint8_t, uint8_t[] );
    void setCursor( uint8_t, uint8_t ); 
    virtual size_t write( uint8_t );
    void command( uint8_t );
    
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

