#include "adc.h"
#include "../include/sysctrl.h"

/******************************************************************************
 * Initializes ADC to use Sample Sequencer #3, triggered by software, no IRQs
 *****************************************************************************/
bool initializeADC(  uint32_t adc_base )
{
  ADC0_Type  *myADC;
  uint32_t rcgc_adc_mask;
  uint32_t pr_mask;
  

  // examine the adc_base.  Verify that it is either ADC0 or ADC1
  // Set the rcgc_adc_mask and pr_mask  
  switch (adc_base) 
  {
    case ADC0_BASE :
    {
      
      // ADD CODE
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R0;
      // Set pr_mask 
			pr_mask  = SYSCTL_PRADC_R0;
      break;
    }
    case ADC1_BASE :
    {
        // ADD CODE
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R1;
      // Set pr_mask 
			pr_mask  = SYSCTL_PRADC_R1;
      break;
    }
    
    default:
      return false;
  }
  
  // Turn on the ADC Clock
  SYSCTL->RCGCADC |= rcgc_adc_mask;
  
  // Wait for ADCx to become ready
  while( (pr_mask & SYSCTL->PRADC) != pr_mask){}
    
  // Type Cast adc_base and set it to myADC
  myADC = (ADC0_Type *)adc_base;
  
  ADC0->ACTSS &= ~ADC_ACTSS_ASEN2; // disable Ss2
		 
	 // set the event multiplexer to trigger conversion on a software trigger
	 // for samplke sequencer #2
	 ADC0->EMUX &= ~ADC_EMUX_EM2_ALWAYS;
		 	 
	 ADC0->SSCTL2 = ADC_SSCTL2_END1|ADC_SSCTL2_IE1;
  
  return true;
}

//******************************************************************************
// Returns the values for the PS2 joystic and potentiometer
//*****************************************************************************
bool get_adc_values( uint32_t adc_base, uint16_t *ps2_x, uint16_t *ps2_y){

  ADC0_Type  *myADC;

  if( adc_base == 0){
    return false;
  }
   
	
   myADC = (ADC0_Type *)adc_base;
	
	 myADC->SSMUX2 = 0x01; // set channel
	
   
	
	 myADC->ACTSS |= ADC_ACTSS_ASEN2;  // Enable SS2
	 myADC->PSSI =   ADC_PSSI_SS2;     // Start SS2
	
	 while( (myADC->RIS & ADC_RIS_INR2)  == 0){}
		
	 *ps2_x = myADC->SSFIFO2 & 0xFFF;    // Read 12-bit data
	
   
		
	 *ps2_y = myADC->SSFIFO2 & 0xFFF;    // Read 12-bit data

   
	
	
   
	 myADC->ISC  = ADC_ISC_IN2;          // Ack the conversion	
  
	 
		
	 return true;
}



