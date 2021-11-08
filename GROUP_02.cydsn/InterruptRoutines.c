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
    Timer_ADC_ReadStatusRegister();
    switch(FlagStatus)
    {
        case 0x01: // Temperature readout
            
            AMux_FastSelect(CH_TEMP);
            if(counter_samples < NUMERO_CAMPIONI) // Campiono fino a quando ho 5 campioni
            {
                temperatura_1 = ADC_DelSig_Read32();
                if(temperatura_1 < 0) temperatura_1 = 0;
                if(temperatura_1 > 65535) temperatura_1 = 65535;
                temperatura_mv = ADC_DelSig_CountsTo_mVolts(temperatura_1);
            
                sum_t = (sum_t + temperatura_mv);
                
                counter_samples ++;
            }
           
            break;
        case 0x02: // Light readout
            AMux_FastSelect(CH_LUCE);
            if(counter_samples < NUMERO_CAMPIONI) // Campiono fino a quando ho 5 campioni
            {
                luce = ADC_DelSig_Read32();
                if(luce < 0) luce = 0;
                if(luce > 65535) luce = 65535;
                luce_mv = ADC_DelSig_CountsTo_mVolts(luce);
            
                sum_l = (sum_l + luce_mv);
                
                counter_samples ++;
            }
            break;
        case 0x03: // Temperature and light readout
            if(counter_samples < NUMERO_CAMPIONI) // Campiono fino a quando ho 5 campioni
            {
                ADC_DelSig_StopConvert();
                AMux_FastSelect(CH_TEMP);
                temperatura_1 = ADC_DelSig_Read32();
                if(temperatura_1 < 0) temperatura_1 = 0;
                if(temperatura_1 > 65535) temperatura_1 = 65535;
                temperatura_mv = ADC_DelSig_CountsTo_mVolts(temperatura_1);
            
                sum_t = (sum_t + temperatura_mv);
                
                ADC_DelSig_StopConvert();
                AMux_FastSelect(CH_LUCE);
                luce = ADC_DelSig_Read32();
                if(luce < 0) luce = 0;
                if(luce > 65535) luce = 65535;
                luce_mv = ADC_DelSig_CountsTo_mVolts(luce);
            
                sum_l = (sum_l + luce_mv);
                
                counter_samples ++;
            }
            
            
            
            break;
        default:   // Rest condition
            break;
    }
    
    if(counter_samples == 5) // Dopo 5 step posso aggioranre i valori nel buffer
    {
        avg_temperatura = sum_t / 5;
        avg_luce = sum_l / 5;
        
        
        slaveBuffer[3] = avg_temperatura >> 8;
        slaveBuffer[4] = avg_temperatura & 0xFF;
        slaveBuffer[5] = avg_luce >> 8;
        slaveBuffer[6] = avg_luce & 0xFF;
        
        // In questo modo counter_sample = 6, non rientro in nessuno dei casi precedenti
        counter_samples ++;
    }
}


void EZI2C_ISR_ExitCallback()
{
    if(FlagStatus != (slaveBuffer[0] & 0x03))
    {
        FlagStatus = (slaveBuffer[0] & 0x03); // Aggiorno lo stato in cui sono
        if (FlagStatus == 0x03) Pin_LED_Write(1);
        else Pin_LED_Write(0);
        
        // Ripristino condizioni di lavoro 
        slaveBuffer[3] = 0;
        slaveBuffer[4] = 0;
        slaveBuffer[5] = 0;
        slaveBuffer[6] = 0;
        
        counter_samples = 0;
        sum_t = 0;
        sum_l = 0;
    }
    
    counter_samples = 0;
    sum_t = 0;
    sum_l = 0;
}


/* [] END OF FILE */
