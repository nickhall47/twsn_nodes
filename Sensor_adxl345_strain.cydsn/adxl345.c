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
#include "adxl345.h"

int accelerometerNotify;

void ADXL345_Start()
{
    SPI_Start();
    ADXL345_WriteReg(ADXL345_REG_DATA_FORMAT, 0x01);
	ADXL345_WriteReg(ADXL345_REG_POWER_CTL, 0x08);
    while(SPI_SpiIsBusBusy());
    SPI_SpiUartClearRxBuffer();

    SPI_Sleep();
}

void ADXL345_Wakeup()
{
    SPI_Wakeup();
}

void ADXL345_Sleep()
{
    while(SPI_SpiIsBusBusy());
    SPI_Sleep();
}

void ADXL345_WriteReg(ADXL345_REG_T reg, uint8 data)
{
    uint8 buffer[2];
    uint32 intrStatus;

    buffer[0] = reg;
    buffer[1] = data;
    
    
    while(SPI_SpiIsBusBusy());
    intrStatus = CyEnterCriticalSection();
    SPI_SpiUartPutArray(buffer, 2);
    CyExitCriticalSection(intrStatus);
}

void ADXL345_ReadReg(ADXL345_REG_T reg, uint8 count)
{
    uint32 intrStatus;
    int i;
    
    reg |= 0x80;
    
    if(count > 1)
        reg |= 0x40;
    
    while(SPI_SpiIsBusBusy());
    SPI_SpiUartClearRxBuffer();
    
    intrStatus = CyEnterCriticalSection();
    SPI_SpiUartWriteTxData(reg);
     
    for(i=0; i<count; i++)
    {
        SPI_SpiUartWriteTxData(0x00);
    }
    
    CyExitCriticalSection(intrStatus);
    
}

void ADXL345_GetMeasurement()
{
    static uint8 buffer[MAX_SPI_RX_BUFFER_SIZE];
    CYBLE_GATTS_HANDLE_VALUE_NTF_T accelerometerHandle;
    
    ADXL345_Wakeup();
    ADXL345_ReadReg(ADXL345_REG_DATAX0, 6);
    
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
        
        if(accelerometerNotify)
        {
            accelerometerHandle.attrHandle = CYBLE_SENSORS_ACCELEROMETER_CHAR_HANDLE;
            accelerometerHandle.value.val = buffer;
            accelerometerHandle.value.len = byteCount;
            
            CyBle_GattsNotification(connectionHandle, &accelerometerHandle);
        }
            
    }
    
    ADXL345_Sleep();
}

/* [] END OF FILE */
