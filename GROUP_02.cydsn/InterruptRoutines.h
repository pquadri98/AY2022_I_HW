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
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    #include "cytypes.h"
    
    #define CH_TEMP 0
    #define CH_LUCE 1
    
    uint8 FlagStatus;
    
    uint32 temperatura_1;
    uint32 temperatura_2;
    
    uint32 avg_temperatura;
    
    CY_ISR_PROTO(Custom_ISR_ADC);

#endif
/* [] END OF FILE */
