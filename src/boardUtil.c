#include "TM4C123GH6PM.h"
#include "boardUtil.h"
#include "sysctrl.h"

#define   LCD_GPIO_BASE       GPIOA_BASE
#define   LCD_SPI_BASE        SSI0_BASE
#define   LCD_CLK_PIN         1 << 2
#define   LCD_CS_PIN          1 << 3
#define   LCD_MOSI_PIN        1 << 5

#define   LCD_CLK_PIN_PCTL    GPIO_PCTL_PA2_SSI0CLK
#define   LCD_CS_PIN_PCTL     GPIO_PCTL_PA3_SSI0FSS
#define   LCD_MOSI_PIN_PCTL   GPIO_PCTL_PA5_SSI0TX


#define   GPIO_LCD_CD_BASE    GPIOA_BASE
#define   LCD_CD_PIN          1 << 4

#define   GPIO_LCD_RST_N_BASE GPIOC_BASE
#define   LCD_RST_N_PIN       1 << 7

void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

//*****************************************************************************
// Configure PA0 and PA1 to be UART pins
//*****************************************************************************
void uart0_config_gpio(void)
{
   gpio_enable_port(GPIOA_BASE);
   gpio_config_digital_enable( GPIOA_BASE, PA0 | PA1);
   gpio_config_alternate_function( GPIOA_BASE, PA0 | PA1);
   gpio_config_port_control( GPIOA_BASE, GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX);
}

//*****************************************************************************
//*****************************************************************************
void serialDebugInit(void)
{
  uart0_config_gpio();
  uart0_init_115K();
}


void gpio_init(void)
{
	//push button pins
	gpio_enable_port(GPIOF_BASE);
	gpio_enable_port(GPIOE_BASE);
	gpio_config_digital_enable(GPIOF_BASE, DIR_BTN_UP | DIR_BTN_DOWN | DIR_BTN_LEFT | DIR_BTN_RIGHT);
	gpio_config_digital_enable(GPIOE_BASE, PS2_BTN);
	gpio_config_analog_enable(GPIOE_BASE, PS2_X_DIR_PIN | PS2_Y_DIR_PIN);
	gpio_config_enable_input(GPIOF_BASE, DIR_BTN_UP | DIR_BTN_DOWN | DIR_BTN_LEFT | DIR_BTN_RIGHT);
	gpio_config_enable_input(GPIOE_BASE, PS2_BTN | PS2_X_DIR_PIN | PS2_Y_DIR_PIN);  
	gpio_config_enable_pullup(GPIOF_BASE, DIR_BTN_UP | DIR_BTN_DOWN | DIR_BTN_LEFT | DIR_BTN_RIGHT);
	gpio_config_enable_pullup(GPIOE_BASE, PS2_BTN);
	gpio_config_alternate_function(GPIOE_BASE, PS2_X_DIR_PIN | PS2_Y_DIR_PIN);
	initializeADC(ADC0_BASE);
	initializeADC(ADC1_BASE);
	
	
}

void lcd_init(void)
{
	// Configure SPI CLK
  gpio_enable_port(LCD_GPIO_BASE);
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_CLK_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_CLK_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_CLK_PIN_PCTL);
    
  // Configure SPI CS
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_CS_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_CS_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_CS_PIN_PCTL);

  // Configure SPI MOSI
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_MOSI_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_MOSI_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_MOSI_PIN_PCTL);
  
  // Configure CD
  gpio_enable_port(GPIO_LCD_CD_BASE);
  gpio_config_digital_enable(GPIO_LCD_CD_BASE,LCD_CD_PIN);
  gpio_config_enable_output(GPIO_LCD_CD_BASE,LCD_CD_PIN);
  
  // Configure RST_N
  gpio_enable_port(GPIO_LCD_RST_N_BASE);
  gpio_config_digital_enable(GPIO_LCD_RST_N_BASE, LCD_RST_N_PIN);
  gpio_config_enable_output(GPIO_LCD_RST_N_BASE, LCD_RST_N_PIN);
 
  // Configure the SPI interface for Mode 3, 25MHz.
  // Make sure to adjust the registers used to determine the frequency of 
  // the SPI clock.
  initialize_spi( LCD_SPI_BASE, 3, 2);
}


void rf_init(void) // REMEMBER TO DELETE IF NOT USED DO NOT TURN IN!!!!
{
	
  wireless_set_pin_config(
    RF_SPI_BASE,
    RF_PAYLOAD_SIZE,
    RF_CHANNEL,
    RF_CS_BASE,
    RF_CS_PIN,
    RF_CE_GPIO_BASE,
    RF_CE_PIN
  );
  
  gpio_enable_port(RF_GPIO_BASE);
  
  // Configure SPI CLK
  gpio_config_digital_enable(RF_GPIO_BASE, RF_CLK_PIN);
  gpio_config_alternate_function(RF_GPIO_BASE, RF_CLK_PIN);
  gpio_config_port_control(RF_GPIO_BASE, RF_CLK_PIN_PCTL);
  
  // Configure SPI MISO
  gpio_config_digital_enable(RF_GPIO_BASE, RF_MISO_PIN);
  gpio_config_alternate_function(RF_GPIO_BASE, RF_MISO_PIN);
  gpio_config_port_control(RF_GPIO_BASE, RF_MISO_PIN_PCTL);
  
  // Configure SPI MOSI
  gpio_config_digital_enable(RF_GPIO_BASE, RF_MOSI_PIN);
  gpio_config_alternate_function(RF_GPIO_BASE, RF_MOSI_PIN);
  gpio_config_port_control(RF_GPIO_BASE, RF_MOSI_PIN_PCTL);
  
  // Configure CS to be a normal GPIO pin that is controlled 
  // explicitly by software
  gpio_config_digital_enable(RF_CS_BASE,RF_CS_PIN);
  gpio_config_enable_output(RF_CS_BASE,RF_CS_PIN);
  
  // Configure CE Pin as an output
  gpio_enable_port(RF_CE_GPIO_BASE);
  gpio_config_digital_enable(RF_CE_GPIO_BASE,RF_CE_PIN);
  gpio_config_enable_output(RF_CE_GPIO_BASE,RF_CE_PIN);
		
  initialize_spi(RF_SPI_BASE, 0, 10);    
  RF_CE_PERIH->DATA |= (1 << 1);
}

//*****************************************************************************
// Initialize the I2C peripheral
//*****************************************************************************
void i2cInit(void)
{
  
  gpio_enable_port(EEPROM_GPIO_BASE);
  
  // Configure SCL 
  gpio_config_digital_enable(EEPROM_GPIO_BASE, EEPROM_I2C_SCL_PIN);
  gpio_config_alternate_function(EEPROM_GPIO_BASE, EEPROM_I2C_SCL_PIN);
  gpio_config_port_control(EEPROM_GPIO_BASE, EEPROM_I2C_SCL_PIN_PCTL);

  
  // Configure SDA 
  gpio_config_digital_enable(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PIN);
  gpio_config_open_drain(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PIN);
  gpio_config_alternate_function(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PIN);
  gpio_config_port_control(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PIN_PCTL);
  
  //  Initialize the I2C peripheral
  initializeI2CMaster(EEPROM_I2C_BASE);
  
}

