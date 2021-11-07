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
            break;
        case 0x02:
            break;
        case 0x03:
            break;
        default:
            break;
    }

}

void EZI2C_ISR_ExitCallback(void)
{
    if(FlagStatus != (slaveBuffer[0] & 0x03))
    {
        FlagStatus = (slaveBuffer[0] & 0x03); // Aggiorno lo stato in cui sono
        if (FlagStatus == 0x03) Pin_LED_Write(1);
        else Pin_LED_Write(0);
        // Ripristino condizioni di lavoro 
    }
}


/* [] END OF FILE */
