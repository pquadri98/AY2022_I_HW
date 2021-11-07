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
#include "project.h"
#include "InterruptRoutines.h"

#define SLAVE_BUFFER_SIZE 7
#define BUFFER_RW_AREA_SIZE 0x02
#define WHO_AM_I_REGISTER 0xBC

uint8_t slaveBuffer[SLAVE_BUFFER_SIZE]; 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Timer_ADC_Start();
    isr_ADC_StartEx(Custom_ISR_ADC);
    
    ADC_DelSig_Start();
    AMux_Start();
    
    
    
    EZI2C_Start();
    
    // Setup slaveBuffer
    // Entrambi status bit pari a zero
    // Predispongo già il numero di campioni per la media pari a 5
    slaveBuffer[0] = 0b00010100; 
    
    // Status bits
    FlagStatus = (slaveBuffer[0] & 0x03);
    
     
    // Timer a 10khz
    // Questo valore può essere modificato cambiando il valore di questo registro
    // Timer 1 Period value predisposto a 10, isr ogni 1 ms
    slaveBuffer[1] = 0x0A; 
    slaveBuffer[2] = WHO_AM_I_REGISTER;
    slaveBuffer[3] = 0;
    slaveBuffer[4] = 0;
    slaveBuffer[5] = 0;
    slaveBuffer[6] = 0;
    
    // Set up EZI2C buffer
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, BUFFER_RW_AREA_SIZE ,slaveBuffer);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
