#include "mcc_generated_files/mcc.h"
#include "OLED.h"

uint16_t pot_value = 0;
uint16_t temp = 0;
char ADCstr[7];
char Tempstr[5];
#define ADCRES  0.0012207 // ADC  per volt = 5/4096 , vcc/adc , 2^12

/* Main application */                       
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    Oled_Init();
    Oled_Clear();
    while (1)
    {   
        pot_value = ADCC_GetSingleConversion(LM35_AND0);
        temp = (pot_value * ADCRES) * 10000;
        sprintf(ADCstr, "%u", pot_value);
        sprintf(Tempstr, "%u%u.%u%u", (temp/1000)%10, (temp/100)%10, (temp/10)%10, ( temp/1)%10);
        
        Oled_SelectPage(0); 
        Oled_WriteString("LM35 Sensor Data:");
        Oled_SelectPage(1);
        Oled_WriteString(Tempstr);
         
        Oled_SelectPage(2); 
        Oled_WriteString("RD0 ADC Data");
        Oled_SelectPage(3);
        Oled_WriteString(ADCstr);
        
        LED_RE0_Toggle();
        __delay_ms(2000);
        Oled_ClearLine(1);
        Oled_ClearLine(3);
    }
}
/* End of File */