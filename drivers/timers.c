#include "timers.h"

//*****************************************************************************
// Configure Timer 0 to be two 16-bit, periodic, count down timers.
// Do not set the values for TAILR or TBILR and DO NOT enable the timer.
//*****************************************************************************
void configure_timer0(void){
	
	// turn on clock for the timer0
	SYSCTL->RCGCTIMER |= SYSCTL_RCGCTIMER_R0;
	
	//wait for the timer to turn on 
	while((SYSCTL->PRTIMER & SYSCTL_PRTIMER_R0) == 0) {};
	
	// turn off the timer before configuration
	TIMER0->CTL &= ~(TIMER_CTL_TAEN);
	
	// Set the timer to be in 32 mode (CFG)
	TIMER0->CFG = TIMER_CFG_32_BIT_TIMER;
	
		// clear any status bits indicating that the time has expired 
	TIMER0->ICR |= TIMER_ICR_TATOCINT;
	
		//Set the Timer A Mode Register to be in periodic mode and count down (TAMR)
	TIMER0->TAMR = TIMER_TAMR_TAMR_PERIOD; 	

}

//*****************************************************************************
// Turns on Timer0A and Turns Off Timer0B.  The TAILR is set to load_value
//*****************************************************************************
void start_timer0A(uint32_t load_value){
	
	// Set the number of clock cycles in the Timer A Interval Load Register (TAILR)
	TIMER0->TAILR = load_value;
	//enabling timeout interrupts		
	TIMER0->IMR =  TIMER_IMR_TATOIM;
	//enabling timer intterupts using NVIC
	NVIC_EnableIRQ(TIMER0A_IRQn);
	NVIC_SetPriority (TIMER0A_IRQn,2);
	// Enable the A timer (CTL)
	TIMER0->CTL |= TIMER_CTL_TAEN|TIMER_CTL_TBEN;
	
	
}

//*****************************************************************************
// Turns off Timer0A.  This function does not alter the load value.
//*****************************************************************************
void stop_timer0A(void){
	// Disable the A timer (CTL)
	TIMER0->CTL &= ~(TIMER_CTL_TAEN);
}
//*****************************************************************************
// initiates watchdog timer  
//***************************************************************************** 
void watchdogInit(uint32_t ticks)
{
  // Turn on the clock gating register for the Watchdog timer
  SYSCTL->RCGCWD |= SYSCTL_RCGCWD_R0;
  // Wait for the timer to turn on
  while( (SYSCTL->PRWD & SYSCTL_RCGCWD_R0) ==0 ) {};
  // Set the Tick Count
  WATCHDOG0->LOAD = ticks;
  // Configure WDT to cause a reset and Enable Interrupts
  // Enable Interrupts
  WATCHDOG0->CTL = WDT_CTL_INTEN | WDT_CTL_RESEN;
  // Set the priority to 1
  NVIC_SetPriority(WATCHDOG0_IRQn,1);
  // Enable the NVIC for the watchdog timer
  NVIC_EnableIRQ(WATCHDOG0_IRQn);
}


//*****************************************************************************
// stops watchdog timer. 
//***************************************************************************** 
void watchdogStop ()
{
  // Turn off the clock gating register for the Watchdog timer
  WATCHDOG0->CTL &= ~0x3;
}

//*****************************************************************************
// initiates watchdog timer  
//***************************************************************************** 
void watchdogStart(uint32_t ticks)
{
  // Set the Tick Count
  WATCHDOG0->LOAD = ticks;
}