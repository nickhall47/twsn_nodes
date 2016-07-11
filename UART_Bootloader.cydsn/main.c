/******************************************************************************
* Project Name      : UART_Bootloader
* File Name         : main.c
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

/******************************************************************************
* Project Description:
* This project must be built before Bootloadable project.
*
* If USB connector is plugged in, the main()function of this program calls the 
* CyBtldr_Start() API. This API performs the entire bootload operation. It 
* communicates with the host. After a successful bootload operation, this API 
* passes control to the application via a software reset.
*
******************************************************************************/

#include <device.h>

#define UART_CLOCK_DIVIDER_AT_48MHZ				34

CY_ISR(WDT_Handler)
{
    if(CySysWdtGetInterruptSource() & WDT_INTERRUPT_SOURCE)
    {
        CySysWdtClearInterrupt(WDT_INTERRUPT_SOURCE);
    }
}

/******************************************************************************
* Function Name: main
*******************************************************************************
* Summary:
*   UART_Bootloader entry point. If USB connector is plugged in, start UART_Bootloader.
*   If not, start EH_Motherboard the bootloadable.
*
* Parameters:
*   None
*
* Return:
*   None - this is main loop and never returns
*
******************************************************************************/
void main()
{
	CyGlobalIntEnable;
    	
	if(USB_DETECT_Read())
	{
	    UART_Start();
        CyDelay(100u);
        UART_UartPutString("UART Bootloader Starting. It will take 10s.\r\n");

        /* This API does the entire bootload operation. After a succesful 
		 * bootload operation, this API transfers program control to the 
		 * new application via a software reset */
	    CyBtldr_Start();
	}
	else
	{
		 /* Schedule Bootloadable to start after reset */
	    Bootloader_SET_RUN_TYPE(Bootloader_START_APP);

	    CySoftwareReset();
	}
	/* CyBtldr_Start() API does not return – it ends with a 
	 * software device reset. So, the code after this API call (below)
	 * is never executed. */
    for(;;)
    {
        /* empty */
    }
}

/* [] END OF FILE */
