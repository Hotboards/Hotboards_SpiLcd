/*
  Hotboards_SpiLcd.cpp - Library for write and control and lcd with spi interfaces and the ST7032 controller.
  base on Liquid Cristal library
  Library ported by diego from Hotboards January 16, 2016. 
  and originally cretaed by
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  Released into the public domain.
*/

#include "Hotboards_SpiLcd.h"
#include <SPI.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

Hotboards_SpiLcd::Hotboards_SpiLcd( int cs, int rs, int rst )
{
    pinMode( cs, OUTPUT );
    pinMode( rs, OUTPUT );
    pinMode( rst, OUTPUT );
    _cs_pin = cs;
    _rs_pin = rs;
    _rst_pin = rst;
}

void Hotboards_SpiLcd::begin( void )
{
    digitalWrite( _cs_pin, HIGH );
    digitalWrite( _rst_pin, LOW );
    delay( 2 );
    digitalWrite( _rst_pin, HIGH );
    delay( 20 );
    command( 0x30 );/*wakeup*/
    delay( 2 );
    command( 0x30 );/*wakeup*/
    command( 0x30 );/*wakeup*/
    
    // configure default display functions, two lines, 5x8 charcters
    _displayfunction = HT_SPILCD_8BITMODE | HT_SPILCD_2LINE | HT_SPILCD_5x8DOTS | HT_SPILCD_EXTINST;
    command( HT_SPILCD_FUNCTIONSET | _displayfunction );
    
    command( 0x14 );/*internaloscfrequency*/
    command( 0x56 );/*powercontroll*/
    command( 0x6d );/*followercontrol*/
    delay( 200 );
    command( 0x70 );/*constrast*/
    
    // reenable shift functions disbling extended instructions
    _displayfunction &= ~HT_SPILCD_EXTINST;
    command( HT_SPILCD_FUNCTIONSET | _displayfunction );
    
    // turn the display on with no cursor or blinking default
    _displaycontrol = HT_SPILCD_DISPLAYON | HT_SPILCD_CURSOROFF | HT_SPILCD_BLINKOFF;  
    display( );
    
    // Initialize to default text direction (for romance languages)
    _displaymode = HT_SPILCD_ENTRYLEFT | HT_SPILCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    command( HT_SPILCD_ENTRYMODESET | _displaymode );
    clear( );/*clearscreen*/
}

void Hotboards_SpiLcd::clear( void )
{
    command( HT_SPILCD_CLEARDISPLAY );  // clear display, set cursor position to zero
    delayMicroseconds( 2000 );          // this command takes a long time!   
}

void Hotboards_SpiLcd::home( void )
{
    command( HT_SPILCD_RETURNHOME );      // set cursor position to zero
    delayMicroseconds( 2000 );          // this command takes a long time!   
}

void Hotboards_SpiLcd::noDisplay( void )
{
    _displaycontrol &= ~HT_SPILCD_DISPLAYON;
    command( HT_SPILCD_DISPLAYCONTROL | _displaycontrol );
}

void Hotboards_SpiLcd::display( void )
{
    _displaycontrol |= HT_SPILCD_DISPLAYON;
    command( HT_SPILCD_DISPLAYCONTROL | _displaycontrol );  
}

void Hotboards_SpiLcd::noBlink( void )
{
    _displaycontrol &= ~HT_SPILCD_BLINKON;
    command( HT_SPILCD_DISPLAYCONTROL | _displaycontrol );
}    
    
void Hotboards_SpiLcd::blink( void )
{
    _displaycontrol |= HT_SPILCD_BLINKON;
    command( HT_SPILCD_DISPLAYCONTROL | _displaycontrol );
}


void Hotboards_SpiLcd::noCursor( void )
{
    _displaycontrol &= ~HT_SPILCD_CURSORON;
    command( HT_SPILCD_DISPLAYCONTROL | _displaycontrol );
}

void Hotboards_SpiLcd::cursor( void )
{
    _displaycontrol |= HT_SPILCD_CURSORON;
    command( HT_SPILCD_DISPLAYCONTROL | _displaycontrol );
  
}

void Hotboards_SpiLcd::scrollDisplayLeft( void )
{
    command( HT_SPILCD_CURSORSHIFT | HT_SPILCD_DISPLAYMOVE | HT_SPILCD_MOVELEFT );
}

void Hotboards_SpiLcd::scrollDisplayRight( void )
{
    command( HT_SPILCD_CURSORSHIFT | HT_SPILCD_DISPLAYMOVE | HT_SPILCD_MOVERIGHT );  
}

void Hotboards_SpiLcd::leftToRight( void )
{
    _displaymode |= HT_SPILCD_ENTRYLEFT;
    command( HT_SPILCD_ENTRYMODESET | _displaymode );
}

void Hotboards_SpiLcd::rightToLeft( void )
{
    _displaymode &= ~HT_SPILCD_ENTRYLEFT;
    command( HT_SPILCD_ENTRYMODESET | _displaymode );  
}

void Hotboards_SpiLcd::autoscroll( void )
{
    _displaymode |= HT_SPILCD_ENTRYSHIFTINCREMENT;
    command( HT_SPILCD_ENTRYMODESET | _displaymode );
}

void Hotboards_SpiLcd::noAutoscroll( void )
{
    _displaymode &= ~HT_SPILCD_ENTRYSHIFTINCREMENT;
    command( HT_SPILCD_ENTRYMODESET | _displaymode );   
}
    
void Hotboards_SpiLcd::setCursor( uint8_t col, uint8_t row )
{
    const uint8_t Buffer[ 2 ]= { 0x00u, 0x40u };
    uint8_t address;
  
    if( row > 1 )
    {
        row = 1;
    }
    address = Buffer[ row ] + col;
    command( 0x80 | address );
}


/*********** mid level commands, for sending data/cmds */
/*
 * Write a character to the LCD.
 * data: the character to write to the display
 */
inline void Hotboards_SpiLcd::command( uint8_t value )
{
    digitalWrite( _cs_pin, LOW );
    send( value, LOW );
    digitalWrite( _cs_pin, HIGH );
    delayMicroseconds( 100 ); // commands need > 27us to settle
}

/*
 * Write a character to the LCD.
 */
inline size_t Hotboards_SpiLcd::write( uint8_t value )
{
    digitalWrite( _cs_pin, LOW );
    send( value, HIGH );
    digitalWrite( _cs_pin, HIGH );
    delayMicroseconds( 100 ); // commands need > 27us to settle
    return 1; // assume sucess
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void Hotboards_SpiLcd::send( uint8_t value, uint8_t mode ) 
{
    digitalWrite( _rs_pin, mode );
    SPI.transfer( value );
}

