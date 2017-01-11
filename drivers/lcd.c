// Copyright (c) 2014-15, Joe Krachey
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
#include "lcd.h"
#include "../src/boardUtil.h"

uint8_t lcd[8][102]; // set using lcd draw // both main and draw use it but main shouldnt change it


// 
//  Image data for maze2crop2
// 

const uint8_t image[] =
{
	// #####################################################################################################
	// #####################################################################################################
	// ##   ##   ##                  ##             #                  ##                       ##        ##
	// ##   ##   ##                  ##             #                  ##                       ##        ##
	// ##   ##   ##                  ##             #                  ##                       ##        ##
	// ##   ##   #######   #######   ##   #######   ######    ######   #######   ##   #######   ##   ##   ##
	// ##   ##   #######   #######   ##   ######    ######    ######   #######   ##   #######   ##   ##   ##
	// ##                  ##        ##        #         #    #    #        ##   ##   ##   ##        ##   ##
	// ##                  ##        ##        #         #    #    #        ##   ##   ##   ##        ##   ##
	// ##                  ##        ##        #         #    #    #        ##   ##   ##   ##        ##   ##
	// ######################   ############   ######    #    #    ######   #######   ##   ############   ##
	// ######################   ############   ######    #    #   #######   #######   ##   ############   ##
	// ##                  ##   ##                  #         #        ##             ##        ##        ##
	// ##                  ##   ##                  #         #        ##             ##        ##        ##
	// ##                  ##   ##                  #         #        ##             ##        ##        ##
	// #######   ############   #################   ################   #################   #######   #######
	// #######   ############   #################   ################   #################   #######   #######
	// ##   ##             ##             ##        #                            ##                       ##
	// ##   ##             ##             ##        #                            ##                       ##
	// ##   ##             ##             ##        #                            ##                       ##
	// ##   ##   #######   ############   ##   ###########    ###########   ##   ##   ######################
	// ##   ##   #######   ############   ##   ###########    ###########   ##   ##   ######################
	// ##   ##   ##                  ##        #              #             ##   ##                       ##
	// ##   ##   ##                  ##        #              #             ##   ##                       ##
	// ##   ##   ##                  ##        #              #             ##   ##                       ##
	// ##   ##   ##   #######   ################    ##########################   ######################   ##
	// ##   ##   ##   #######   #################   ##########################   ######################   ##
	// ##        ##        ##   ##                                     ##             ##        ##        ##
	// ##        ##        ##   ##                                     ##             ##        ##        ##
	// ##        ##        ##   ##                                     ##             ##        ##        ##
	// ##   ############   ##   ##   ###############################   ############   #######   ##   #######
	// ##   ############   ##   ##   ###############################   ############   #######   ##   #######
	// ##   ##             ##   ##                       #    #    #             ##             ##        ##
	// ##   ##             ##   ##                       #    #    #             ##             ##        ##
	// ##   ##             ##   ##                       #    #    #             ##             ##        ##
	// #######   ############   #####################    #    #    ###########   ######################   ##
	// #######   ############   #####################    #    #   ############   ######################   ##
	// ##        ##        ##        ##                  #                  ##                  ##        ##
	// ##        ##        ##        ##                  #                  ##                  ##        ##
	// ##        ##        ##        ##                  #                  ##                  ##        ##
	// ##   #######   ##   ############   ################    ###############################   ##   #######
	// ##   #######   ##   ############   ################    ###############################   ##   #######
	// ##             ##                  ##        #    #                       ##   ##        ##        ##
	// ##             ##                  ##        #    #                       ##   ##        ##        ##
	// ##             ##                  ##        #    #                       ##   ##        ##        ##
	// ##   ################################   ##   #    #####################   ##   ##   #######   #######
	// ##   ################################   #    #    #####################   ##   ##   #######   #######
	// ##   ##                  ##             #                                      ##        ##        ##
	// ##   ##                  ##             #                                      ##        ##        ##
	// ##   ##                  ##             #                                      ##        ##        ##
	// ##   ##   ############   ##   ##############################################   #######   ##   #######
	// ##   ##   ############   ##   ##############################################   #######   ##   #######
	//      ##             ##        ##             #         #                  ##   ##        ##        ##
	//      ##             ##        ##             #         #                  ##   ##        ##        ##
	//      ##             ##        ##             #         #                  ##   ##        ##        ##
	// ##   ############   ############   #######   #    #    #   ############   ##   ##   ############   ##
	// ##   ############   ############   ######    #    #    #   ############   ##   ##   ############   ##
	// ##                  ##                  #         #                  ##        ##                    
	// ##                  ##                  #         #                  ##        ##                    
	// ##                  ##                  #         #                  ##        ##                    
	// #####################################################################################################
	// #####################################################################################################
	0xFF, 0xFF, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x63, 0x63, 0x63, 0x63, 0x63, 0x03, 0x03, 0x03, 0xE3, 0xE3, 0x63, 0x63, 0x63, 0x63, 0x63, 0x03, 0x03, 0x03, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x63, 0x63, 0x63, 0x63, 0x63, 0xE3, 0x23, 0x03, 0x03, 0x03, 0x7F, 0x63, 0x63, 0x63, 0x63, 0xE3, 0x03, 0x03, 0x03, 0x03, 0xE3, 0x63, 0x63, 0x63, 0x63, 0xE3, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0xE3, 0xE3, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x03, 0x03, 0x03, 0xE3, 0xE3, 0x03, 0x03, 0x03, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x0C, 0x0C, 0x0C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x8C, 0x8C, 0x8C, 0x8F, 0x8F, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x80, 0x80, 0x80, 0x8F, 0x8C, 0x0C, 0x0C, 0x0C, 0xFC, 0x80, 0x80, 0x80, 0x80, 0x8F, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x80, 0x80, 0x80, 0x88, 0x8F, 0x0C, 0x0C, 0x0C, 0xFC, 0xFC, 0x80, 0x80, 0x80, 0x8F, 0x8F, 0x8C, 0x8C, 0x8C, 0x8F, 0x8F, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x8F, 0x8F, 0x8C, 0x8C, 0x8C, 0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x8F, 0x8F, 0x80, 0x80, 0x80, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF1, 0xF1, 0x31, 0x31, 0x31, 0x31, 0x31, 0x01, 0x01, 0x01, 0x3F, 0x3F, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0xF1, 0xF1, 0x01, 0x01, 0x01, 0x3F, 0x3F, 0x01, 0x01, 0x01, 0xF1, 0x31, 0x30, 0x30, 0x30, 0x3F, 0x31, 0x31, 0x31, 0x31, 0x31, 0x01, 0x01, 0x01, 0x01, 0xF1, 0x31, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31, 0x01, 0x01, 0x01, 0xF1, 0xF1, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x31, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xC7, 0xC7, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC6, 0xC6, 0x06, 0x06, 0x06, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x06, 0x06, 0x06, 0xC7, 0xC7, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC7, 0xC4, 0xC0, 0xC0, 0xC0, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC7, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x06, 0x06, 0x06, 0xFE, 0xFE, 0xC6, 0xC6, 0xC6, 0xC7, 0xC7, 0xC0, 0xC0, 0xC0, 0xC7, 0xC7, 0x06, 0x06, 0x06, 0xFE, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x06, 0x06, 0x06, 0xFE, 0xFE, 0x06, 0x06, 0x06, 0xC6, 0xC6, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x10, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xE3, 0xE3, 0x63, 0x63, 0x63, 0x63, 0x63, 0x60, 0x60, 0x60, 0x7F, 0x7F, 0x60, 0x60, 0x60, 0x63, 0x63, 0x63, 0x63, 0x63, 0xE3, 0xE3, 0x63, 0x63, 0x63, 0x63, 0x63, 0x60, 0x60, 0x60, 0x7F, 0x7F, 0x03, 0x03, 0x03, 0xE3, 0x23, 0x03, 0x03, 0x03, 0x7F, 0x03, 0x03, 0x03, 0x03, 0x7F, 0x60, 0x60, 0x60, 0x60, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x03, 0x03, 0x03, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x63, 0x63, 0x60, 0x60, 0x60, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0xFF, 0xFF, 
	0x8F, 0x8F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x0C, 0x0C, 0x0C, 0xFC, 0xFC, 0x80, 0x80, 0x80, 0x8F, 0x8F, 0x80, 0x80, 0x80, 0xFC, 0xFC, 0x0C, 0x0C, 0x0C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8F, 0x8C, 0x0C, 0x0C, 0x0C, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x8C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFC, 0x0C, 0x0C, 0x0C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x8C, 0x0C, 0x0C, 0x0C, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0C, 0x0C, 0x0C, 0x8C, 0x8C, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x8C, 0x8C, 0x0C, 0x0C, 0x0C, 0xFF, 0xFF, 
	0x3F, 0x3F, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30, 0x3F, 0x3F, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x3F, 0x3F, 0x30, 0x30, 0x30, 0x31, 0x31, 0x30, 0x30, 0x30, 0x3F, 0x3F, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x30, 0x31, 0x31, 
};





//*****************************************************************************
// Use the GPIO port connected to the LCD Reset line to hold the 
// LCD in reset.  The signal is active low
// 
// ADD CODE
//*****************************************************************************
__INLINE static void dogs102_assert_reset(void)
{
	GPIOC->DATA &= ~(1<<7);
}

//*****************************************************************************
// Use the GPIO port connected to the LCD Reset line to bring the 
// LCD out of reset by setting the pin high
// 
// ADD CODE
//*****************************************************************************
__INLINE static void dogs102_deassert_reset(void)
{
  GPIOC->DATA |= (1<<7);
}

//*****************************************************************************
// The LCD can be put into command mode by writing a 0 to the CMD pin.  
// In command mode, you can set the active page or page.
// 
// ADD CODE
//*****************************************************************************
__INLINE static void dogs102_assert_cmd_mode(void)
{
	GPIOA->DATA &= ~(1<<4);
}

//*****************************************************************************
// Turn OFF command mode by writeing a 1 to the CMD pin
//
// When the LCD is not in command command mode, any data that is written over
// the SPI interface is treated as data to turn ON/OFF pixels at the location
// indicated by the currently active page and column.
// 
// ADD CODE
//*****************************************************************************
__INLINE static void dogs102_deassert_cmd_mode(void)
{
  GPIOA->DATA |= (1<<4);
}

//*****************************************************************************
// Set the page address to page 7-0.  The orientation of the 353 carrier card
// puts page 0 at the top of the display and page 7 at the bottom.
//
// See "Set Page Address" in the EADOGS102W-6 data sheet, pg 5.
//
// Make sure to set the command mode correctly!
// 
// ADD CODE
//*****************************************************************************
void dogs102_set_page(uint8_t page)
{
		uint8_t tx_data;
		uint8_t rx_data;
    
		//Enter Command Mode
    dogs102_assert_cmd_mode();
    
		// Set the active page using spiTx
	  tx_data = 0xB0 | (page & 0x0F);
		spiTx(SSI0_BASE, &tx_data, 1, &rx_data);
    
    //Exit Command Mode
		dogs102_deassert_cmd_mode();
}

//*****************************************************************************
// There are 102 columns in the display.  Use this function to set which colum
// data will be written to.
//
// See "Set Column Address LSB and MSB" in the EADOGS102W-6 data sheet, pg 5.
// This will require two different SPI transactions.
//
// Make sure to set the command mode correctly!
  // 
// ADD CODE
//*****************************************************************************
void dogs102_set_column(uint8_t column)
{

	uint8_t tx_data;
  uint8_t rx_data;
	uint8_t column_low4;
	uint8_t column_up4;
	
	column_low4 = column & 0x0F;
	column_up4 = (column & 0xF0) >> 4;
	
	
  //Enter Command Mode
  dogs102_assert_cmd_mode();

  // Set the active column LSB using spiTx
	
	tx_data = 0x00 | column_low4;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
	
  // Set the active column MSB using spiTx
  tx_data = 0x10 | column_up4;
	spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
	
  //Exit Command Mode
	dogs102_deassert_cmd_mode();
}

//*****************************************************************************
// When not in command mode, any data written to the LCD is used to determine
// which pixels are turned ON/OFF for the curretnly active page.  A 1 turns a 
// pixel on and a 0 turns the pixel off.
// 
// ADD CODE
//*****************************************************************************
void dogs102_write_data( uint8_t data)
{
  uint8_t tx_data;
  uint8_t rx_data;
	
  //Exit Command Mode
  dogs102_deassert_cmd_mode();
  
	// Send the data using spiTx
	tx_data = data;
	spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
}

  
//*****************************************************************************
// PROVIDED CODE
//*****************************************************************************  

//*****************************************************************************
// Supports writing a 10 point character to the LCD.  There are "4" lines on 
// the LCD,
//*****************************************************************************
 void dogs102_write_char_10pts( uint8_t line, char c, uint8_t charIndex)
  {
    
    uint16_t i, index;
    uint8_t upperPage, lowerPage;
    
    switch (line)
    {
      case 0:
      {
        upperPage = 0;
        lowerPage = 1;
        break;
      }
      
       case 1:
      {
        upperPage = 2;
        lowerPage = 3;
        break;
      }
      
       case 2:
      {
        upperPage = 4;
        lowerPage = 5;
        break;
      }
      
      case 3:
      {
        upperPage = 6;
        lowerPage = 7;
        break;
      }
    }
    if(c >= 32 || c <= 126)
    {
      
      index = c - 32;
      index = index * 20;
      
      dogs102_set_page(upperPage) ;
      
      for( i=0; i< 10; i++)
      {
        dogs102_set_column(charIndex*10 + i);
        dogs102_write_data(courierNew_10ptBitmaps[index+i]);
      }
      
      dogs102_set_page(lowerPage) ;
      
      for( i=10; i< 20; i++)
      {
        dogs102_set_column(charIndex*10 + (i-10));
        dogs102_write_data(courierNew_10ptBitmaps[index+i]);
      }

    }

  }

//*****************************************************************************
// Used to clear the LCD of all pixels
//*****************************************************************************
void dogs102_clear(void)
{
  uint8_t page;
  uint8_t colCount;
  
  for(page = 0; page < 8; page++)
  {
      dogs102_set_page(page) ;

      for( colCount=0; colCount< 102; colCount++)
      {
        dogs102_set_column(colCount);
        dogs102_write_data(0x00);
      }
    }
}

//*****************************************************************************
// Provided initialization code for the LCD.  Found in the data sheet.
//*****************************************************************************
void dogs102_init(void)
{
  uint8_t tx_data;
  uint8_t rx_data;

  
  //Take the LCD out of reset
  dogs102_deassert_reset();
  
  //Enter Command Mode
  dogs102_assert_cmd_mode();
  
 //Set Scroll Line
  tx_data = 0x40;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set SEG Directions
  tx_data = 0xA1;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set COM direction
  tx_data = 0xC0;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set All Pixel on
  tx_data = 0xA4;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set Inverse Display
  tx_data = 0xA6;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //et LCD Bias Ratio
  tx_data = 0xA2;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set Power Control
  tx_data = 0x2F;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set VLCD Resistor Ratio
  tx_data = 0x27;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set Electronic Volume
  tx_data = 0x81;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  tx_data = 0x10;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
  //Set Adv Program Control
  tx_data = 0xFA;
  spiTx(SSI0_BASE, &tx_data, 1, &rx_data);
  tx_data = 0x90;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);
  
 //Set Display Enable
  tx_data = 0xAF;
  spiTx(SSI0_BASE,&tx_data, 1, &rx_data);

  //Exit Command Mode
  dogs102_deassert_cmd_mode();
  
}

//*****************************************************************************
// string write: writes a string of up to 10 letters that are 10 pixels tall
// on 1 of the 4 lines
//*****************************************************************************
 void dogs102_write_string( char* string, uint8_t line){
	 
	 int i;
	 
	 for(i=0; i<10; i++){
		
		 dogs102_write_char_10pts( line, string[i], i);
	 }
 }

//*****************************************************************************
// get_data: gives data value of a page column 
// used to help movement at speed 2 pixels appear smoother when moving towards a 
// boundry
//*****************************************************************************

uint8_t get_data(uint8_t y_pos){
  
	 uint8_t data;
	  
	 if (y_pos<8){ 
		 data = y_pos ;
		 data = (1<<data);
	 } 
	 else{
			data = y_pos%8;
			data = (1<<data);
	 }
  return data;	  	 
}	
/*
*****************************************************************************
// square set: sets the coord square array of a player using the top left coord
// then updates center coord for later use
*****************************************************************************

void player_square_set(Player *player){
	
	 int r; //row index
	 int c; // column index
	 
	 int x_start = player->top_left_corner.x;
	 int y_start = player->top_left_corner.y;
	  
	
	
	 for( r = 0; r < 5; r++){// traverse rows
		 
     for(c = 0; c < 5; c++){
         
			 player->square[r][c].x = x_start + c;
			 player->square[r][c].y = y_start + r;
     }			 
   }		 
	player->center_position.x = player->square[2][2].x;
	player->center_position.y = player->square[2][2].y;
}

*/

//*****************************************************************************
// change image[] data to w-D array with 1's and 0's representing each pixel on
// the screen. Then it places a single pixel for the player's cursor on the 2-D
// array and then prints the whole thing onto the screen.
//*****************************************************************************

void print_lcd(Player *player){ // REMEMBER TO UPGRADE LCD.h
/*	uint8_t lcd[64][102];
	uint8_t temp[8][102];
	uint8_t page_data, data;
	int i,j, page, shift;
	bool firstRow;
	page = 0;
	shift = 1;
  
	dogs102_init();
  dogs102_clear();
  
	// converts image (1D array) to 2D array called temp
  for(i = 0; i < 8; i++)
  {
    for(j = 0; j < 101; j++)
    {
			temp[i][j] = image[i*101 + j];
    }
  }
	
	// last two rows on the screen are blank
	for(i = 0; i < 102; i++) {
		lcd[62][i] = 0;
		lcd[63][i] = 0;
	}
	//also perhaps need to set the last column to all zeros
	
	for(i = 0; i < 62; i++)
  {
		if (i % 8 == 0 && i >= 8) page++;
    for(j = 0; j < 101; j++)
    {
			page_data = temp[page][j];
			if ((page_data & shift) != 0)
				lcd[i][j] = 1;
			else
				lcd[i][j] = 0;
			
			if (shift == 256)
				shift = 1;
			else 
				shift = shift*2;
    }
  }
	
	
	// set the values of the player's coordinates on the 2D array after verifying collision
	if (lcd[player->current.x][player->current.y] != 1)
		lcd[player->current.x][player->current.y] = 1;
	else {
		player->current.x = player->previous.x;
		player->current.y = player->previous.y;
		lcd[player->current.x][player->current.y] = 1;
	}
	
	
	//print the whole 2D array
	shift = 0;
	page = 0;
	page_data = 0;
	firstRow = false;
	for(i = 0; i < 64; i++)
  {
    if (i % 8 == 0 && i >= 8) page++;
    for(j = 0; j < 102; j++)
    {
			
			// at the first row of every page
			if ((i % 8 == 0) && (i == 0 || i >= 8))
				temp[page][j] = lcd[i][j];
			page_data |= temp[page][j];
			page_data = page_data << 1;
			page_data = lcd[i][j];
			temp[page][j] |= page_data;
			
			
    }
  }
	*/
	
	
	
	
	/////////////////////////////////////////////////
	//uint8_t lcd[8][102];
	uint8_t page, new_data;
	int i, j;
	
	// converts image write values (1D array) to 2D array called lcd
  for(i = 0; i < 8; i++)
  {
    for(j = 0; j < 101; j++)
    {
			lcd[i][j] = image[i*101 + j];
    }
  }
	
	page = player->current.y / 8;
	if (player->current.y < 8){ 
		 new_data = player->current.y;
		 new_data = (1 << new_data);
	}
	else {
			new_data = player->current.y % 8;
			new_data = (1 << new_data);
	}
	
	
	// REMOVED COLLISION CHECKING FOR ONE PIXEL FROM PRINT LCD
	// BECAUSE HAVING IT IN DIFFERENT FUNCTION WAS NOT FAST ENOUGH
	// AND CAUSED GLITCHES WITH WALLS AND MADE THE MOVEMENT LAGGY
	// MUCH SMOOTHER MOVEMENT NOW
	// BOTH 1 PIXEL AND 2 PIXEL SPEED COLLISION CHECK NOW DONE AT MOVEMENT
	// SECTION IN MAIN BEFORE UPDATING CURRENT POSITION
  // SO WE DONT NEED PREVIEOS POS VARIABLE ANY MORE
	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	// verifies if collision with wall
	//if ((lcd[page][player->current.x] & new_data) != 0) {
		////collision occurred
		//player->current.x = player->previous.x;
		//player->current.y = player->previous.y;
		//recalculate new_data so that it's set to previous position
		//if (player->current.y < 8){ 
		 //new_data = player->current.y;
		 //new_data = (1 << new_data);
		//}
		//else {
			//new_data = player->current.y % 8;
			//new_data = (1 << new_data);
		//}	
	//}
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	
	// set position of the player (one pixel) in the maze
	lcd[page][player->current.x] |= new_data;
	
	// print out the 2D array onto the lcd
	for(i = 0; i < 8; i++)
  {
    dogs102_set_page(i);
    for(j=0; j<101; j++)
    {
      dogs102_set_column(j);
      dogs102_write_data(lcd[i][j]);
    }
  }
}










