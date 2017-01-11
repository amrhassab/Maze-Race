#ifndef __LCD_H__
#define __LCD_H__

#include <stdint.h>
#include "spi.h"
#include "fonts.h"

#define NUM_PAGES   8
#define NUM_COLS    102

// Copyright (c) 2014, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

extern const uint8_t image[];


//*****************************************************************************
// player structure coordinate 5X5 square
//*****************************************************************************


typedef struct coord
{
	uint8_t x;
	uint8_t y;	
}Coord;


typedef struct player
{
	Coord current;
	//Coord previous; not needed any more 
	// but we should keep player struct because might need more 
	//properties such as win = true/false and time completed etc...
}Player;





//*****************************************************************************
// Provided initialization code for the LCD.  Found in the data sheet.
//*****************************************************************************
void dogs102_init(void);

//*****************************************************************************
// Set the page address to page 7-0.  The orientation of the 353 carrier card
// puts page 0 at the top of the display and page 7 at the bottom.
//
// See "Set Page Address" in the EADOGS102W-6 data sheet, pg 5.
//
// Make sure to set the command mode correctly!
//*****************************************************************************
void dogs102_set_page(uint8_t   page);

//*****************************************************************************
// There are 102 columns in the display.  Use this function to set which colum
// data will be written to.
//
// See "Set Column Address LSB and MSB" in the EADOGS102W-6 data sheet, pg 5.
// This will require two different SPI transactions.
//
// Make sure to set the command mode correctly!
//*****************************************************************************
void dogs102_set_column(uint8_t   column);

//*****************************************************************************
// When not in command mode, any data written to the LCD is used to determine
// which pixels are turned ON/OFF for the curretnly active page.  A 1 turns a 
// pixel on and a 0 turns the pixel off.
//*****************************************************************************
void dogs102_write_data( uint8_t   data);
  

//*****************************************************************************
// Supports writing a 10 point character to the LCD.  There are "4" lines on 
// the LCD,
//*****************************************************************************
void dogs102_write_char_10pts( uint8_t line, char c, uint8_t charIndex);

//*****************************************************************************
// Used to clear the LCD of all pixels
//*****************************************************************************
void dogs102_clear(void);

//*****************************************************************************
// string write: writes a string of up to 10 letters that are 10 pixels tall
// on 1 of the 4 lines
//*****************************************************************************
 void dogs102_write_string( char* string, uint8_t line);

//*****************************************************************************
// get_data: gives data value of a page column 
// used to help movement at speed 2 pixels appear smoother when moving towards a 
// boundry
//*****************************************************************************

uint8_t get_data(uint8_t y_pos);

//*****************************************************************************
// square set: sets the coord square array of a player using the top left coord
// then updates center coord for later use
//*****************************************************************************

//void player_square_set(Player *player); // not needed might use later


//*****************************************************************************
// change image[] data to w-D array with 1's and 0's representing each pixel on
// the screen. Then it places a single pixel for the player's cursor on the 2-D
// array and then prints the whole thing onto the screen.
//*****************************************************************************

void print_lcd(Player *player);

#endif
