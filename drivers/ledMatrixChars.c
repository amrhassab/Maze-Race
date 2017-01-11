#include "../include/ledMatrixChars.h"


const uint8_t LedNumbers[16][5] = 
{
   { // 0
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED6_ON, 
      LED0_ON & LED6_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
   },
   { // 1
      LED_ALL_OFF, 
      LED_ALL_OFF, 
      LED_ALL_OFF, 
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 2
      LED_ALL_OFF, 
      LED0_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED6_ON
   },
   { // 3
      LED_ALL_OFF, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 4
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON,  
      LED3_ON, 
      LED3_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 5
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED6_ON,
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 6
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 7
      LED_ALL_OFF , 
      LED0_ON , 
      LED0_ON , 
      LED0_ON , 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 8
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 9
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON , 
      LED0_ON & LED3_ON,  
      LED0_ON & LED3_ON,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 10
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON ,  
      LED0_ON & LED3_ON ,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 11
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED3_ON & LED6_ON,  
      LED3_ON & LED6_ON,  
       LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 12
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED6_ON, 
      LED0_ON & LED6_ON, 
      LED0_ON & LED6_ON,
   },
   { // 13
      LED_ALL_OFF, 
      LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED3_ON & LED6_ON,  
      LED3_ON & LED6_ON,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 14
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON
   },
   { // 15
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED3_ON,  
      LED0_ON & LED3_ON,  
      LED0_ON & LED3_ON
   }
} ;
