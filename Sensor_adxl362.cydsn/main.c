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
#include "adxl362.h"

uint8 newDataSemaphore = 0;

int main()
{

    CyGlobalIntEnable;
    CyBle_Start(BLE_Stack_Handler);
    ADXL362_Start();


    for(;;)
    {

        CyBle_ProcessEvents();

        if(bleConnected && newDataSemaphore)
        {
            newDataSemaphore = 0;
            ADXL362_GetMeasurement();
        }
            
        BLE_Low_Energy_Handler();
        
    }
}

/* [] END OF FILE */
