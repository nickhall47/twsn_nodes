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

#ifndef ADXL362_H_
    #define ADXL362_H_
    
    #include <project.h>
    
    	/// Type that is used for referencing internal registers of the ADXL362 chip
	enum ADXL362_REG_T {
		ADXL362_REG_DEVID = 0x00,				///< Device ID
		ADXL362_REG_DEVID_MST = 0x01,
        ADXL362_PARTID = 0x02,
        ADXL362_REG_REVID = 0x03,
        ADXL362_REG_XDATA = 0x08,
        ADXL362_REG_YDATA = 0x09,
        ADXL362_REG_ZDATA = 0x0A,
        ADXL362_REG_STATUS = 0x0B,
        ADXL362_REG_FIFO_ENTRIES_L = 0x0C,
        ADXL362_REG_FIFO_ENTRIES_H = 0xD,
        ADXL362_REG_XDATA_L = 0x0E,
        ADXL362_REG_XDATA_H = 0x0F,
        ADXL362_REG_YDATA_L = 0x10,
        ADXL362_REG_YDATA_H = 0x11,
        ADXL362_REG_ZDATA_L = 0x12,
        ADXL362_REG_ZDATA_H = 0x13,
        ADXL362_REG_TEMP_L = 0x14,
        ADXL362_REG_TEMP_H = 0x15,
        ADXL362_REG_SOFT_RESET = 0x1F,
        ADXL362_REG_THRESH_ACT_L = 0x20,
        ADXL362_REG_THRESH_ACT_H = 0x21,
        ADXL362_REG_TIME_ACT = 0x22,
        ADXL362_REG_THRESH_INACT_L = 0x23,
        ADXL362_REG_THRESH_INACT_H = 0x24,
        ADXL362_REG_TIME_INACT_L = 0x25,
        ADXL362_REG_TIME_INACT_H = 0x26,
        ADXL362_REG_ACT_INACT_CTL = 0x27,
        ADXL362_REG_FIFO_CONTROL = 0x28,
        ADXL362_REG_FIFO_SAMPLES = 0x29,
        ADXL362_REG_INTMAP1 = 0x2A,
        ADXL362_REG_INTMAP2 = 0x2B,
        ADXL362_REG_FILTER_CTL = 0x2C,
        ADXL362_REG_POWER_CTL = 0x2D,
        ADXL362_REG_SELF_TEST = 0x2E
        
	};
    
    typedef enum ADXL362_REG_T ADXL362_REG_T;

    
    #define MAX_SPI_RX_BUFFER_SIZE 256
    
    extern void ADXL362_Start();
    extern void ADXL362_Wakeup();
    extern void ADXL362_Sleep();
    extern void ADXL362_WriteReg(ADXL362_REG_T reg, uint8 data);
    extern void ADXL362_ReadReg(ADXL362_REG_T reg, uint8 count);
    extern void ADXL362_GetMeasurement();
    
#endif


/* [] END OF FILE */
