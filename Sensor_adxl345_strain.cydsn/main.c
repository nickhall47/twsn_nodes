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

#include "common.h"
#include "ble_handler.h"
#include "adxl345.h"
#include "strain.h"
#include <stdlib.h>

uint8 newDataSemaphore = 0;

int main()
{
    // Random delay
    uint32 seed = 0;
    CyGetUniqueId(&seed);
    srand(seed);
    uint8 randNum = rand();
    CyDelay(randNum*10);
    
    DEBUG_PIN_Write(1);

    CyGlobalIntEnable;
    
    ADXL345_Start();
    Strain_Start();
    CyBle_Start(BLE_Stack_Handler);

    for(;;)
    {

        CyBle_ProcessEvents();

        if(bleConnected && newDataSemaphore)
        {
            newDataSemaphore = 0;
            Strain_GetMeasurement();
            ADXL345_GetMeasurement();
        }
            
        BLE_Low_Energy_Handler();
        
    }
}

/* [] END OF FILE */
