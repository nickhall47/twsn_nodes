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
#include "adxl362.h"

int accelerometerNotify;

void ADXL362_Start()
{
    SPI_Start();
    ADXL362_WriteReg(ADXL362_REG_SOFT_RESET, 0x52);
	ADXL362_WriteReg(ADXL362_REG_POWER_CTL, 0x0A);
    
    SPI_Sleep();
}

void ADXL362_Wakeup()
{
    SPI_Wakeup();
}

void ADXL362_Sleep()
{
    while(SPI_SpiIsBusBusy());
    SPI_Sleep();
}

void ADXL362_WriteReg(ADXL362_REG_T reg, uint8 data)
{
    uint8 buffer[3];
    uint32 intrStatus;

    buffer[0] = 0x0A; // Register read byte
    buffer[1] = reg;
    buffer[2] = data;
    
    
    while(SPI_SpiIsBusBusy());
    intrStatus = CyEnterCriticalSection();
    SPI_SpiUartPutArray(buffer, 3);
    CyExitCriticalSection(intrStatus);
}

void ADXL362_ReadReg(ADXL362_REG_T reg, uint8 count)
{
    uint8 buffer[2];
    uint32 intrStatus;
    int i;
    
    buffer[0] = 0x0B; // Register read byte
    buffer[1] = reg;
    
    
    while(SPI_SpiIsBusBusy());
    SPI_SpiUartClearRxBuffer();
    intrStatus = CyEnterCriticalSection();
    SPI_SpiUartPutArray(buffer, 2);
     
    for(i=0; i<count; i++)
    {
        SPI_SpiUartWriteTxData(0x00);
    }
    
    CyExitCriticalSection(intrStatus);
    
}

void ADXL362_GetMeasurement()
{
    static uint8 buffer[MAX_SPI_RX_BUFFER_SIZE];
    CYBLE_GATTS_HANDLE_VALUE_NTF_T accelerometerHandle;
    
    ADXL362_Wakeup();
    ADXL362_ReadReg(ADXL362_REG_XDATA_L, 6);
    
    while(SPI_SpiIsBusBusy());
    uint32 byteCount = SPI_SpiUartGetRxBufferSize();
    
    if(byteCount > 0)
    {
        uint32 i;
        for(i=0; i<byteCount; i++)
        {
            buffer[i] = SPI_SpiUartReadRxData();
        }
        
        SPI_SpiUartClearRxBuffer();
        
        // Hard-coded data:
        // To make sure it works
        byteCount = 6;
        buffer[0] = 0x00;
        buffer[1] = 0xFF;
        buffer[2] = 0x00;
        buffer[3] = 0x01;
        buffer[4] = 0x00;
        buffer[5] = 0x02;
        
        
        
        if(accelerometerNotify)
        {
            accelerometerHandle.attrHandle = CYBLE_SENSORS_ACCELEROMETER_CHAR_HANDLE;
            accelerometerHandle.value.val = buffer;
            accelerometerHandle.value.len = byteCount;
            
            CyBle_GattsNotification(connectionHandle, &accelerometerHandle);
        }
            
    }
    
    ADXL362_Sleep();
}

/* [] END OF FILE */
