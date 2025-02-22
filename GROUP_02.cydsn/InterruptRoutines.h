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
    uint8 counter_samples;
    uint8 PeriodoTimer;
    uint8 MeanReady;
    
    int32 temperatura_mv;
    int32 temperatura_1;
    int32 avg_temperatura;
    int32 sum_t;
    
    int32 luce_mv;
    int32 luce;
    int32 avg_luce;
    int32 sum_l;
    
    CY_ISR_PROTO(Custom_ISR_ADC);
    CY_ISR_PROTO(Custom_ISR_50Hz);

#endif
/* [] END OF FILE */
