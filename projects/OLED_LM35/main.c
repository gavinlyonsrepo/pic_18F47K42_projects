

// ************ Libs ****************
#include "mcc_generated_files/mcc.h"
#include "OLED.h"

//************** Globals ****************
uint8_t testcount = 1;

//*************** Defines *************
#define VCC 5
#define ADC 4096
#define ADCRES  0.0012207 // ADC  per volt = 5/4096 , vcc/adc , 2^12
#define TESTDELAY   5000

// ********* Function prototypes ************
void Setup(void);
void DisplayData(void);

// ********* Main Loop **********          
void main(void)
{
    Setup();
    while (1)
    {       
        DisplayData();
        LED_RE0_Toggle();
        testcount++;
        __delay_ms(TESTDELAY);        
    }
}
// *********  End of Main Loop ************


// *********  Function Space ************

// Function to setup PIC
void Setup(void)
{
  SYSTEM_Initialize();
  Oled_Init();
  Oled_Clear();
  Oled_SelectPage(0); 
  Oled_WriteString("RD0 ADC Data:");
  Oled_SelectPage(2); 
  Oled_WriteString("RD0 Volt Data:");
  Oled_SelectPage(4); 
  Oled_WriteString("LM35 Sensor Data:");
  Oled_SelectPage(6); 
  Oled_WriteString("Testcount:");
}

// Function to display sensor data
void DisplayData(void)
{
        char ADCstr[12];
        uint16_t pot_value = 0;
        uint16_t voltage = 0;
        
        Oled_ClearLine(1);
        Oled_ClearLine(3);
        Oled_ClearLine(5);
        
        pot_value = ADCC_GetSingleConversion(LM35_AND0);
        sprintf(ADCstr, "%u ADC", pot_value);
        Oled_SelectPage(1);
        Oled_WriteString(ADCstr);

        voltage = (pot_value * ADCRES) * 100; // eg 2000 * 5/4096 = 2.44 V 
        sprintf(ADCstr, "%u%u.%u%u V", (voltage/1000)%10, (voltage/100)%10, (voltage/10)%10, ( voltage/1)%10);
        Oled_SelectPage(3);
        Oled_WriteString(ADCstr);
        
        pot_value = (pot_value * ADCRES) * 10000; // eg 140 * 5/4096 = 170mV or 17 degrees
        sprintf(ADCstr, "%u%u.%u%u C", (pot_value/1000)%10, (pot_value/100)%10, (pot_value/10)%10, ( pot_value/1)%10);
        Oled_SelectPage(5);
        Oled_WriteString(ADCstr);
        
        sprintf(ADCstr, "%u", testcount);
        Oled_SelectPage(7);
        Oled_WriteString(ADCstr);
}


/* End of File */

