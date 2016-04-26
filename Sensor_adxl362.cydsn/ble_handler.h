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

#ifndef BLE_HANDLER_H_
    #define BLE_HANDLER_H_

    #include <project.h>
    
    extern uint8 newDataSemaphore;
    
    extern void BLE_Stack_Handler( uint32 eventCode, void *eventParam);
    extern void BLE_Low_Energy_Handler();
    
#endif

/* [] END OF FILE */
