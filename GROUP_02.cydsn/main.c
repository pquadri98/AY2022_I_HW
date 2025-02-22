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

// Versione Finale


#include "project.h"
#include "InterruptRoutines.h"

#define SLAVE_BUFFER_SIZE 7 // Numero di registri nel buffer
#define BUFFER_RW_AREA_SIZE 0x02 // Numero di registri R/W
#define WHO_AM_I_REGISTER 0xBC 

uint8_t slaveBuffer[SLAVE_BUFFER_SIZE]; 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Inizializzazione delle periferiche
    Timer_ADC_Start();
    isr_ADC_StartEx(Custom_ISR_ADC);
    Timer_50Hz_Start();
    isr_50Hz_StartEx(Custom_ISR_50Hz);
    
    
    ADC_DelSig_Start();
    AMux_Start();
    
    EZI2C_Start();
    
    // Setup slaveBuffer
    // Entrambi status bit pari a zero
    // Campioni per media = 0
    // Attendiamo inserimento valori da BCP
    slaveBuffer[0] = 0b000000000; 
    
    // Estrazione bit per il controllo delle operazioni
    FlagStatus = (slaveBuffer[0] & 0x03);
    
     
    // Timer a 10khz
    // Timer ADC Period value = 0x0A
    slaveBuffer[1] = PeriodoTimer;
    
    // Registri only Read
    slaveBuffer[2] = WHO_AM_I_REGISTER;
    slaveBuffer[3] = 0; // Ch0 Bit 15-8
    slaveBuffer[4] = 0; // Ch0 Bit 07-0
    slaveBuffer[5] = 0; // Ch1 Bit 15-8
    slaveBuffer[6] = 0; // Ch1 Bit 07-0
    
    // Set up EZI2C buffer
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, BUFFER_RW_AREA_SIZE ,slaveBuffer);
    
    // Aspettiamo 5ms affinchè tutto si inizializzi correttamente
    CyDelay(5);
    

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
