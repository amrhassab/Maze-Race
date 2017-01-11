#include "interrupts.h"
#include "wireless.h"
#include "timers.h"
#include "eadogs102w.h"

extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART0_Tx_Buffer;

extern volatile bool AlertSysTick;
extern volatile bool AlertTimer0;

//*****************************************************************************
// Rx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Rx_Flow(PC_Buffer *rx_buffer)
{
  // Remove entries from the RX FIFO until they are all removed
  while( !(UART0->FR & UART_FR_RXFE ))
  {
    if( ! pc_buffer_full(rx_buffer))
    {
      // Add the character to the circular buffer
      pc_buffer_add(rx_buffer,UART0->DR);
    }
  }

  // Clear the RX interrupts so it can trigger again when the hardware 
  // FIFO becomes full
  UART0->ICR |= (UART_ICR_RXIC | UART_ICR_RTIC);
}

//*****************************************************************************
// Tx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Tx_Flow(PC_Buffer *tx_buffer)
{
      char c;
  
        // Check to see if we have any data in the circular queue
        if( ! pc_buffer_empty(tx_buffer))
        {
            // Move data from the circular queue to the hardware FIFO
            // until the hardware FIFO is full or the circular buffer
            // is empty.
            while( (! pc_buffer_empty(tx_buffer)) && !(UART0->FR & UART_FR_TXFF ) )
            {
              pc_buffer_remove(tx_buffer, &c);  
              UART0->DR = c;
            }
        }
        else
        {
            // Any data in the hardware FIFO will continue to be transmitted
            // but the TX empty interrupt will not be enabled since there
            // is no data in the circular buffer.

            // Disable the TX interrupts.
            UART0->IM &= ~UART_IM_TXIM;
        }
        
        // Clear the TX interrupt so it can trigger again when the hardware
        // FIFO is empty
        UART0->ICR |= UART_ICR_TXIC;
}

// SysTick Handler
void SysTick_Handler(void)
{
   uint32_t val;
   //static int count = 0;
  
   //count = (count + 1) % 10;
  
   //if( count == 0)
   //{
     // Alert the main application the SysTick Timer has expired
     AlertSysTick = true;
   //}

   // clear WATCHDDOG0 Interrupt
   //WATCHDOG0->ICR = 0;
   
   // Clears the SysTick Interrupt
   val = SysTick->VAL;
}


#define WATCHDOG_LOCK_VAL        0x1ACCE551
#define WATCHDOG_DISABLE        0x00000000

/****************************************************************************
 * Interrupt Service Routine for the watchdog timer
 * DO NOT MODIFY this routine
 ****************************************************************************/
void WDT0_Handler(void)
{
    int tminus = 2;
		dogs102_clear();
		//dogs102_write_char_10pts(0,"No data");
		//dogs102_write_char_10pts(1,"from radio.");
		//dogs102_write_char_10pts(2,"Resetting");
		//dogs102_write_char_10pts(3,"in 3 sec.");
		WATCHDOG0->LOAD = 50000000*3;
		// Countdown to reset
		while(1)
		{
			if(WATCHDOG0->VALUE / 50000000 != tminus)
			{
				tminus = WATCHDOG0->VALUE / 50000000;
				if(tminus == 1)
				{
					//dogs102_write_char_10pts(3,"in 2 sec.");
				}
				else if(tminus == 0){
				//dogs102_write_char_10pts(3,"in 1 sec.");
			}
		}
	}
}
  
//*****************************************************************************
// UART0 Interrupt Service handler
//*****************************************************************************
void UART0_Handler(void)
{
    uint32_t  status;

    // Check to see if RXMIS or RTMIS is active
    status = UART0->MIS;

    if ( status & (UART_MIS_RXMIS | UART_MIS_RTMIS ) )
    {
       UART0_Rx_Flow(&UART0_Rx_Buffer);
    }

    // Check the TX interrupts
    if ( status & UART_MIS_TXMIS )
    {
      UART0_Tx_Flow(&UART0_Tx_Buffer);
    }
    return;
}

void TIMER0A_Handler(void)
{
	AlertTimer0 = true;
	TIMER0->ICR = TIMER_ICR_TATOCINT;

}

void GPIOD_Handler(void)
{
	
	GPIOD->ICR |= 0x80;
	WATCHDOG0->ICR = 0;
	
}
