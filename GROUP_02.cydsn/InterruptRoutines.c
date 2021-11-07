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
        case 0x01: // Temperature readout
            ADC_DelSig_StopConvert();
            AMux_Select(CH_TEMP);

            temperatura = ADC_DelSig_Read32();
            temperatura = ADC_DelSig_CountsTo_mVolts(temperatura);
            
            slaveBuffer[3] = (temperatura >> 8);
            slaveBuffer[4] = (temperatura & 0xFF);
            
            break;
        case 0x02: // Light readout
            break;
        case 0x03: // Temperature and light readout
            break;
        default:   // Rest condition
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
