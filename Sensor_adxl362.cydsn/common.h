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

#ifndef COMMON_H_
    #define COMMON_H_
    
    // Common libraries
    #include <project.h>
    
    // Notification Flags
    extern int accelerometerNotify;
    //extern int strainNotify;
    
    // Bluetooth LE connection variables
    extern int bleConnected;
    extern CYBLE_CONN_HANDLE_T connectionHandle;
    
#endif

/* [] END OF FILE */
