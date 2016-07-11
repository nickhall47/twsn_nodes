/******************************************************************************
* Project Name      : UART_Bootloader
* File Name         : device.h
* Version           : 1.00
* Device Used       : CYBLE-022001-00
* Software Used     : PSoC Creator 3.2 SP1
* Compiler          : ARM GCC 4.8.4
* Related Hardware  : EH_Motherboard
*
*******************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation. All Rights Reserved.
*******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above 
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. 
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement. 
******************************************************************************/

#ifndef DEVICE_H
#define DEVICE_H
    
#include <project.h>

#define USE_WCO_FOR_TIMING (0u)
	
#define WDT_INTERRUPT_SOURCE                        CY_SYS_WDT_COUNTER0_INT    
#define COUNT_PERIOD                                ((uint32)32767/2)
#define COUNTER_ENABLE                              (1u)    
#define SOURCE_COUNTER                              (0u)

#endif
/* [] END OF FILE */
