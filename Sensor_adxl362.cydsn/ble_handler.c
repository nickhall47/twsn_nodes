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

int bleConnected = 0;
CYBLE_CONN_HANDLE_T connectionHandle;

void BLE_Stack_Handler( uint32 eventCode, void *eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
    
    switch( eventCode )
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
            Advertising_LED_Write(0);       // Turn on Advertising LED
            bleConnected = 0;
            break;
            
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
            {
                CySysPmSetWakeupPolarity(CY_PM_STOP_WAKEUP_ACTIVE_HIGH);
                CySysPmStop();
            }
            break;
            
        case CYBLE_EVT_GATT_CONNECT_IND:
            connectionHandle = *(CYBLE_CONN_HANDLE_T *) eventParam;
            Advertising_LED_Write(1);       // Turn off Advertising LED
            bleConnected = 1;
            break;
        
        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            if (wrReq->handleValPair.attrHandle == CYBLE_SENSORS_ACCELEROMETER_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &connectionHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                accelerometerNotify = wrReq->handleValPair.value.val[0];
            }

            
            if(eventCode == CYBLE_EVT_GATTS_WRITE_REQ)
            {   
                CyBle_GattsWriteRsp( connectionHandle );
            }
            break;
            
        default:
            break;
    }
         
}

void BLE_Low_Energy_Handler()
{
    CYBLE_BLESS_STATE_T blessState;
    uint8 intrStatus;
    
    CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
    intrStatus = CyEnterCriticalSection();
    blessState = CyBle_GetBleSsState();
    
    if(blessState == CYBLE_BLESS_STATE_ECO_ON || blessState == CYBLE_BLESS_STATE_DEEPSLEEP)
    {
        CySysPmDeepSleep();
        newDataSemaphore = 1;
    }
    else if(blessState != CYBLE_BLESS_STATE_EVENT_CLOSE)
    {
        CySysPmSleep();
    }
    else
    {
    }
    CyExitCriticalSection(intrStatus);
}

/* [] END OF FILE */
