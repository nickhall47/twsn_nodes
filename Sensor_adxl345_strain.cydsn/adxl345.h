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

#ifndef ADXL345_H_
    #define ADXL345_H_
    
    #include <project.h>
    
    	/// Type that is used for referencing internal registers of the ADXL345 chip
	enum ADXL345_REG_T {
		ADXL345_REG_DEVID = 0x00,				///< Device ID
		ADXL345_REG_THRESH_TAP = 0x1D,			///< Tap threshold
		ADXL345_REG_OFSX = 0x1E,				///< X-axis offset
		ADXL345_REG_OFSY = 0x1F,				///< Y-axis offset
		ADXL345_REG_OFSZ = 0x20,				///< Z-axis offset
		ADXL345_REG_DUR = 0x21,					///< Tap duration
		ADXL345_REG_LATENT = 0x22,				///< Tap latency
		ADXL345_REG_WINDOW = 0x23,				///< Tap window
		ADXL345_REG_THRESH_ACT = 0x24,			///< Activity threshold
		ADXL345_REG_THRESH_INACT = 0x25,		///< Inactivity threshold
		ADXL345_REG_TIME_INACT = 0x26,			///< Inactivity time
		ADXL345_REG_ACT_INACT_CTL = 0x27,		///< Axis enable control for activity and inactivity detection
		ADXL345_REG_THRESH_FF = 0x28,			///< Free-fall threshold
		ADXL345_REG_TIME_FF = 0x29,				///< Free-fall time
		ADXL345_REG_TAP_AXES = 0x2A,			///< Axis control for single tap/double tap
		ADXL345_REG_ACT_TAP_STATUS = 0x2B,		///< Source of single tap/double tap
		ADXL345_REG_BW_RATE = 0x2C,				///< Data rate and power mode control
		ADXL345_REG_POWER_CTL = 0x2D,			///< Power-saving features control
		ADXL345_REG_INT_ENABLE = 0x2E,			///< Interrupt enable control
		ADXL345_REG_INT_MAP = 0x2F,				///< Interrupt mapping control
		ADXL345_REG_INT_SOURCE = 0x30,			///< Source of interrupts
		ADXL345_REG_DATA_FORMAT = 0x31,			///< Data format control
		ADXL345_REG_DATAX0 = 0x32,				///< X-Axis Data 0
		ADXL345_REG_DATAX1 = 0x33,				///< X-Axis Data 1
		ADXL345_REG_DATAY0 = 0x34,				///< Y-Axis Data 0
		ADXL345_REG_DATAY1 = 0x35,				///< Y-Axis Data 1
		ADXL345_REG_DATAZ0 = 0x36,				///< Z-Axis Data 0
		ADXL345_REG_DATAZ1 = 0x37,				///< Z-Axis Data 1
		ADXL345_REG_FIFO_CTL = 0x38,			///< FIFO control
		ADXL345_REG_FIFO_STATUS = 0x39			///< FIFO status
	};
    
    typedef enum ADXL345_REG_T ADXL345_REG_T;

	/** @name Reset vectors
	 *	Macros for the reset vectors for the registers
	 */
	///@{
	#define ADXL345_RESET_DEVID 0xE5			///< Reset vector for DEVID
	#define ADXL345_RESET_DEFAULT 0x00			///< Reset vector for general registers
	#define ADXL345_RESET_BW_RESET 0x0D			///< Reset vector for BW_RESET
	#define ADXL345_RESET_INT_SOURCE 0x02		///< Reset vector for INT_SOURCE
	/// @}
	
	/// Definitions for interrupt modes that can be used
	enum ADXL345_MODE_T {
		ADXL345_MODE_ACT = 0x01,		///< Activity Interrupt
		ADXL345_MODE_NONE = 0x00		///< Disable all interrupts
	};
    
    #define MAX_SPI_RX_BUFFER_SIZE 256
    
    extern void ADXL345_Start();
    extern void ADXL345_Wakeup();
    extern void ADXL345_Sleep();
    extern void ADXL345_WriteReg(ADXL345_REG_T reg, uint8 data);
    extern void ADXL345_ReadReg(ADXL345_REG_T reg, uint8 count);
    extern void ADXL345_GetMeasurement();
    
#endif


/* [] END OF FILE */
