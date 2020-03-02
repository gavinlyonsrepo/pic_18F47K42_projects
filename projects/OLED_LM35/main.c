

#include "mcc_generated_files/mcc.h"
#include "OLED.h"
static uint16_t adcResult; // Used to store the result of the ADC
char temp[10];

/* Main application */
                         
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    Oled_Init();
    Oled_Clear();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    while (1)
    {
        // adcResult = ADCC_GetSingleConversion(LM35_AND0) >> 12;
        // Add your application code
       Oled_SelectPage(0); 
       Oled_WriteString("LM35");
        //Oled_SelectPage(2); 
        //Oled_WriteString("ADC value RC0 Data:");
        //Oled_SelectPage(3);
       // sprintf(temp, "%u ", adcResult);
        //Oled_WriteString(temp);
        __delay_ms(3000);
        LED_RE0_Toggle();
    }
}
/* End of File */

