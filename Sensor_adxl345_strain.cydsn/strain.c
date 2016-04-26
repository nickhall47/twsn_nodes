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
#include "strain.h"

int strainNotify;

void Strain_Start()
{
    ADC_Start();
    Strain_Sleep();
}

void Strain_WakeUp()
{
    ADC_Wakeup();
}

void Strain_Sleep()
{
    ADC_Sleep();
}

void Strain_GetMeasurement()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T strainHandle;

    uint8 result[2];
    uint16 result16;
    
    Strain_WakeUp();
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    result16 = ADC_GetResult16(0);
    result[0] = result16 >> 8;
    result[1] = (uint8) result16;
    
    if(strainNotify)
    {
        strainHandle.attrHandle = CYBLE_SENSORS_STRAIN_CHAR_HANDLE;
        strainHandle.value.val = result;
        strainHandle.value.len = 2;
            
        CyBle_GattsNotification(connectionHandle, &strainHandle);
    }
    Strain_Sleep();
}


/* [] END OF FILE */
