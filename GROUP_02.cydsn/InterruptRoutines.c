/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "InterruptRoutines.h"
#include "project.h"

extern uint8_t slaveBuffer[];


CY_ISR(Custom_ISR_ADC)
{
    switch(FlagStatus)
    {
        case 0x01:
            Pin_LED_Write(0);
            break;
        
        case 0x02:
            Pin_LED_Write(0);
            break;
        
        case 0x03:
            Pin_LED_Write(1);
            break;
        
        default:
            Pin_LED_Write(0);
            break;
    }
}

void EZI2C_ISR_ExitCallback(void)
{
    if(FlagStatus != (slaveBuffer[0] & 0x03))
    {
        FlagStatus = (slaveBuffer[0] & 0x03); // Aggiorno lo stato in cui sono
        // Ripristino condizioni di lavoro 
    }
}


/* [] END OF FILE */
