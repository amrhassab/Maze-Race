//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>  
#include "boardUtil.h"

#include "TM4C123.h"


volatile bool AlertSysTick = false;
volatile bool AlertTimer0 = false;
extern uint8_t lcd[8][102];



uint8_t student1[80];
uint8_t student2[80];
uint8_t teamNumber[3]; // extra spot for null character
uint8_t input[80]; // temporary holding space 


void initializeBoard(void)
{
	
	
  DisableInterrupts();
  serialDebugInit();
	gpio_init();
	lcd_init();
	dogs102_init();
	

  	rf_init();
    configure_timer0();
	  start_timer0A(25000);
//	wireless_configure_device( array1, array2);
//	wireless_configure_device(myID, remoteID);
	i2cInit();
//	ioExpanderInit(IO_EXPANDER_I2C_BASE);
	SysTick_Config(50000);
  EnableInterrupts();
}

//*****************************************************************************
// Function that tests if adc x and y directions are working
//*****************************************************************************
void test_adc(uint16_t *x_data, uint16_t *y_data)
{
	
	 
	 int i;
	 get_adc_values(ADC0_BASE, x_data, y_data);
    
   //printf("X Dir value : 0x%03x        Y Dir value : 0x%03x\r",*x_data, *y_data);
   for( i=0;i<1000000; i++){}
	
	
}
//*****************************************************************************
//*****************************************************************************


//*****************************************************************************
// Function that prints out an image.  The image is 56 pixels by 56 pixels.
// You can try to center the image if you like, but its not necessary.
//*****************************************************************************
void test_lcd(void)
{
  int i,j;
  
  dogs102_init();

  dogs102_clear();
  
  for(i = 0; i < 8; i++)
  {
    
     dogs102_set_page(i);
    for(j=0; j<101; j++)
    {
      dogs102_set_column(j);
      dogs102_write_data(image[i*101 + j]);
    }
  }
}

//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
// Function that reads student1,student2 and team# from EEPROM
// 
//*****************************************************************************
void read_EEPROM(void){
	
	int i;
  for(i = 0; i < 80; i++)
  {
    eeprom_byte_read(EEPROM_I2C_BASE,i,&(student1[i])); 
	}	 
				 
		
	for(i = 80; i < 160; i++)
  {

    eeprom_byte_read(EEPROM_I2C_BASE,i,&(student2[i-80])); 
	}	 
		 
	  eeprom_byte_read(EEPROM_I2C_BASE,160,&(teamNumber[0]));
	  eeprom_byte_read(EEPROM_I2C_BASE,161,&(teamNumber[1]));
	 
}

//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
// Function that writes student1,student2 and team# to EEPROM
// 
//*****************************************************************************
	 
void write_EEPROM(void){
  
	int i;
  for(i = 0; i < 80; i++)
  {
    eeprom_byte_write(EEPROM_I2C_BASE,i,student1[i]);
  }
	
	// Write deafult student2 data to the EEPROM
  for(i = 80; i < 160; i++)
  {
    eeprom_byte_write(EEPROM_I2C_BASE,i,student2[i-80]); // passing i +80 so we dont overwrite
		                                                         // student 1 info
  }
	
	// write team numbers
	eeprom_byte_write(EEPROM_I2C_BASE,(160),teamNumber[0]);
	eeprom_byte_write(EEPROM_I2C_BASE,(161),teamNumber[1]);
}
//*****************************************************************************
//*****************************************************************************

int 
main(void)
{
	///// variables and declarations //////
	
	// button debouncing and other button related variables
	uint32_t btn_data, ps2_btn_data, counter_up_button, 
					 counter_down_button, counter_left_button, counter_right_button, counter_ps2_button;
	bool ps2_pressed = false;
	
	// adc value x y
  uint16_t x_data, y_data;
	
	// pixel movement collision checking
	Player player_1;
	uint8_t test_y, test_x, test_data, test_page;
	uint8_t test_yy, test_xx, test_data2, test_page2;
	

	
	//misilaneous
	int i;
	/// end of variables and declarations //
//	char array1 = {llll}
//	char[]


   
	 
	 
	initializeBoard();
	read_EEPROM(); //fills student1,student2,team arrays
	// printing after array read
	
	printf("\n\r");
  printf("***************************************\n\r");
  printf("Welcome To MAZE RACE \n\r");
  printf("\tStudent 1: %s\n\r", student1);
  printf("\tStudent 2: %s\n\r", student2);
	printf("\tTeam Number: %s\n\r", teamNumber);
  printf("****************************************\n\r");
	
	
	 

 
  // pixel start position at maze entrance
  player_1.current.y = 53;
  player_1.current.x = 1;

  counter_up_button = 0;
	counter_down_button = 0;
	counter_left_button = 0;
	counter_right_button = 0; 
	counter_ps2_button = 0;
	
	// wireless_configure_device( array1, array2);
 
  
  while(1){
		
		dogs102_clear();      
	  print_lcd(&player_1);  //screen refresh every iteration 
		
		
	 
		
		
		
		
		//////////////////////////////////////////////
  	////// systic debouncing of buttons /////// 	
		
    if( AlertSysTick == true ) {
     // ADC sequence should be initiated
		 
     AlertSysTick = false; // resetting boolean
	 
	   
		
     // get button data
     btn_data = GPIOF->DATA;
     ps2_btn_data = GPIOE->DATA;
        
     // debounce each button for 16ms
     if ((btn_data & DIR_BTN_UP) == 0)
      counter_up_button++;
     else
      counter_up_button = 0;
   
     if ((btn_data & DIR_BTN_DOWN) == 0)
      counter_down_button++;
     else
      counter_down_button = 0;
   
     if ((btn_data & DIR_BTN_LEFT) == 0)
      counter_left_button++;
     else
      counter_left_button = 0;
   
     if ((btn_data & DIR_BTN_RIGHT) == 0)
      counter_right_button++;
     else
      counter_right_button = 0;
   
     if ((ps2_btn_data & PS2_BTN) == 0)
      counter_ps2_button++;
     else
      counter_ps2_button = 0;
    
     if (counter_up_button == 1)
       puts("up");
     if (counter_down_button == 1)
       puts("down");
     if (counter_left_button == 1)
       puts("left");
     if (counter_right_button == 1)
       puts("right");
     if (counter_ps2_button == 1){
       //puts("ps2");   
       ps2_pressed = true;
		 } 
   }
	 //// end of debouncing //////////////
	 ////////////////////////////////////
	 
	 
	if(AlertTimer0){
	 
		 AlertTimer0 = false;
		 
		  //updating x and y vaules every 0.5 ms
	    test_adc(&x_data, &y_data ); 
	}
	 
	 
	 	 ////////////////////////////////
	 //// START of PS2 button code /////
	 if(ps2_pressed){ // get player information
		 
		 ps2_pressed = false;
		 read_EEPROM();
		 
		 printf("Student information change request initiated.\n");
     printf("Field Values available for editing: \n\r");
     printf("\n\r");
		 printf("Student 1: %s\n\r", student1);
     printf("Student 2: %s\n\r", student2);
	   printf("Team Number: %s\n\r", teamNumber);
		 printf("\n\r");
		 printf("press ENTER after promt to maintain saved field \n\r");
		 printf("\n\r");
		 
		 // student 1
     printf("please enter a new name for Student 1:");
		 scanf("%79[^\n]", input);
     
		 
		 if(input[1] != 0x00){
			 
			 for( i = 0; i<80; i++){
			  student1[i] = input[i];
			 }
		 }else printf("Student 1 field not modified\n\r");
		 
		 
		 // student 2
     printf("please enter a new name for Student 2:");
		 scanf("%79[^\n]", input);
     
		 
		 if(input[0] != 0x00){
			 
			 for( i = 0; i<80; i++){
			  student2[i] = input[i];
			 }
			 
		 }else printf("Student 2 field not modified\n\r");
	   
		 // team #
		 printf("Enter a new Team Number:");
		 scanf("%2[^\n]", input);
     
		 
		 if(input[0] != 0x00){
			 
			 teamNumber[0] = input[0];
			 teamNumber[1] = input[1]; 
			 teamNumber[2] = input[2]; // to get the null character
			 
		 }else printf("Team# field field not modified\n\r");
	 
	   printf("values have been updated \n\r");
		 write_EEPROM();
	 }
	 
	 
	  //// END of ps2 button code code ////
	 //////////////////////////////////
	 
	 //////////////////////////////////////////////
	 /////// pixel movement using x y adc 	///////
		
		// y axis movement
		
		if (y_data < 0x415 ){ 
		  // if two positions down not a collision
			// move down two pixels
			// else move down one pixel if one pixel causes no collision
			
			test_y = player_1.current.y + 2;
			test_yy = player_1.current.y + 1;
			test_x = player_1.current.x;
			test_data = get_data(test_y);
			test_data2 = get_data(test_yy);
			test_page = test_y / 8;
			test_page2 = test_yy / 8;
			
			if((lcd[test_page][test_x] & test_data) != 0){
				// collision two steps away only move one step
			 
				
				if((lcd[test_page2][test_x] & test_data2) != 0){
				//collision do notining
				}
				else{
				  //player_1.previous.y = player_1.current.y;
				  player_1.current.y = player_1.current.y++;
				}
			}
			else if((lcd[test_page2][test_x] & test_data2) == 0){ // move two pixels after checking for wall of 1 pixel
				//player_1.previous.y = player_1.current.y;
				player_1.current.y = player_1.current.y + 2;
			}
			
		} else if ( y_data >= 0x415 && y_data < 0x7E4 ){
			// move down with speed of one pixel 
				test_y = player_1.current.y + 1;
			  test_x = player_1.current.x;
			  test_data = get_data(test_y);
			  test_page = test_y / 8;
			  if((lcd[test_page][test_x] & test_data) != 0){ }
				else{
				  //player_1.previous.y = player_1.current.y;
				  player_1.current.y = player_1.current.y++;
				}
		
			
		} else if ( y_data >= 0x7E4 && y_data <= 0x7F8){
			// dont move in y direction	
			
		} else if ( y_data > 0x7F8 && y_data <= 0xAA7){
			// move up with speed of 1 pixel
				test_y = player_1.current.y - 1;
			  test_x = player_1.current.x;
			  test_data = get_data(test_y);
			  test_page = test_y / 8;
			  if((lcd[test_page][test_x] & test_data) != 0){ }
				else{
				  //player_1.previous.y = player_1.current.y;
				  player_1.current.y = player_1.current.y--;
				}
			
		} else if ( y_data > 0xAA7 ){
			// if two positions down not a collision
			// move up two pixels
			// else move up one pixel -print lcd handles collision due to one pixel movement
      test_y = player_1.current.y - 2;
			test_yy = player_1.current.y - 1;
			test_x = player_1.current.x;
			test_data = get_data(test_y);
			test_data2 = get_data(test_yy);
			test_page = test_y / 8;
			test_page2 = test_yy / 8;

			if((lcd[test_page][test_x] & test_data) != 0){
				// collision two steps away only move one step if no collison
			
				if((lcd[test_page2][test_x] & test_data2) != 0){
				// still collision do nothing
				}
				else{
				//player_1.previous.y = player_1.current.y;
				player_1.current.y = player_1.current.y--;
				}
			}
			else if((lcd[test_page2][test_x] & test_data2) == 0){ //move two pixels if no one pixel wall int he way
			//player_1.previous.y = player_1.current.y;
			player_1.current.y = player_1.current.y - 2;	
			}
			
		} 
		
		// x- axis movement
		
		if (x_data > 0xBFF ){ 
		  // if two positions back not a collision
			// move back two pixels
			// else move back one pixel -print lcd handles collision due to one pixel movement
			test_y = player_1.current.y;
			test_x = player_1.current.x - 2;
			test_xx = player_1.current.x - 1;
			test_data = get_data(test_y);
			test_page = test_y / 8;
			
			if((lcd[test_page][test_x] & test_data) != 0 ){
			
				if((lcd[test_page][test_xx] & test_data) != 0 ){}
				else{
					//player_1.previous.x = player_1.current.x;
				  player_1.current.x = player_1.current.x - 1;	
				}
				
			}else if((lcd[test_page][test_xx] & test_data) == 0 ){
				//player_1.previous.x = player_1.current.x;
				player_1.current.x = player_1.current.x - 2;
			}
			
		} else if (x_data > 0x80A  && x_data <= 0xBFF){
			// move back with speed of one pixel
				test_y = player_1.current.y;
			  test_x = player_1.current.x - 1;
			  test_data = get_data(test_y);
			  test_page = test_y / 8;
				if((lcd[test_page][test_x] & test_data) != 0 ){}
				else{
					//player_1.previous.x = player_1.current.x;
				  player_1.current.x = player_1.current.x - 1;	
				}
			
		} else if (x_data <= 0x80A && x_data >= 0x7F6 ){
			// dont move in the x direction
			
		} else if ( x_data < 0x7F6 && x_data >= 0x41D){
			//move forward with speed of one pixel
				test_y = player_1.current.y;
			  test_x = player_1.current.x + 1;
			  test_data = get_data(test_y);
			  test_page = test_y / 8;
				if((lcd[test_page][test_x] & test_data) != 0 ){}
				else{
					//player_1.previous.x = player_1.current.x;
				  player_1.current.x = player_1.current.x + 1;	
				}
			
		} else if ( x_data < 0x41D ){
		  // if two positions forward not a collision
			// move forward two pixels
			// else move forward one pixel 
			test_y = player_1.current.y;
			test_x = player_1.current.x + 2;
			test_xx = player_1.current.x + 1;
			test_data = get_data(test_y);
			test_page = test_y / 8;
			
			if((lcd[test_page][test_x] & test_data) != 0){
				
				if((lcd[test_page][test_xx] & test_data) != 0 ){}
				else{
					//player_1.previous.x = player_1.current.x;
				  player_1.current.x = player_1.current.x + 1;	
				}
			}else if((lcd[test_page][test_xx] & test_data) == 0 ){
			  //player_1.previous.x = player_1.current.x;
				player_1.current.x = player_1.current.x + 2;
			}	
		}
    /// end of pixel movement ////		
		///////////////////////////////	 
  }
   
}
