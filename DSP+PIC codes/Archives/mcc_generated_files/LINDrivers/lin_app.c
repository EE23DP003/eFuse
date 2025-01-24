/**
  LIN Slave Application
	
  Company:
    Microchip Technology Inc.

  File Name:
    lin_app.c

  Summary:
    LIN Slave Application

  Description:
    This source file provides the interface between the user and 
    the LIN drivers.

 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "lin_app.h"
#include "../../efuse.h"
#include "../mcc.h"

void LIN_Slave_Initialize(void){

    LIN_init(TABLE_SIZE, scheduleTable, processLIN);
    
}

void processLIN(void){
    uint8_t tempRxData[8];
    uint8_t cmd;

    cmd = LIN_getPacket(tempRxData);
    switch(cmd){
        case LIN_COMMAND:
            CmdOutput(tempRxData[0]);
            break;
        case LIN_TRIGGER_TYPE:
            triggerType = tempRxData[0];
            break;
        case LIN_ENTER_SLEEP_MODE:
            CmdOutput(0);
            LIN_EN_SetLow();
            break;
        case LIN_TJ_LIMIT:
            tj_limit = tempRxData[0];
            break;
        case LIN_FACTOR_RDSON_RTHJS:
            factor_rdson_rthjs = (uint16_t) (tempRxData[1] << 8) | tempRxData[0];
            break;
        case LIN_FACTOR_RDSON_RTHSA:
            factor_rdson_rthsa = (uint16_t) (tempRxData[1] << 8) | tempRxData[0];
            break;
        case LIN_CURRENT2COUNTS_SQUARED:
            current2counts_squared = (uint16_t) (tempRxData[1] << 8) | tempRxData[0];
            break;
        case LIN_ISENSE_MAX:
            isense_max = (uint16_t) (tempRxData[1] << 8) | tempRxData[0];
            break;
        case LIN_DAC_I_HW_TRIP:
            dac_i_hw_trip = tempRxData[0];
            EFuseInit();
            break;
        case LIN_B1_COEF:
            b1_coef = tempRxData[0];
            a1_coef = 0xffff - (2 * b1_coef) + 1;
            break;
        case LIN_REDUCED_DRIVE_TIME:
            reduced_drive_time = tempRxData[0];
            break;
        case LIN_TCC_SAMPLE_TIME:
            tcc_sample_time = (uint16_t) (tempRxData[1] << 8) | tempRxData[0];
            break;
        case LIN_OUTPUT_STATE:
            break;
        case LIN_GET_TRIGGER_TYPE:
            break;
        case LIN_OVER_CURRENT_FAULT:
            break;
        case LIN_UVLO_FAULT:
            break;
        case LIN_OVER_TEMP_FAULT:
            break;
        case LIN_ADC_VCC_SENSE:
            break;
        case LIN_ADC_CURRENT_SENSE_UNCORRECTED:
            break;
        case LIN_ADC_TEMP_SENSE:
            break;
        case LIN_ADC_CURRENT_SENSE_CORRECTED:
            break;
        case LIN_CURRENT_SENSE_OFFSET:
            break;
        case LIN_AMBIENT_TEMPERATURE:
            break;
        case LIN_HEATSINK_TEMPERATURE:
            break;
        case LIN_JUNCTION_TEMPERATURE:
            break;
        case LIN_TEMPERATURE_RISE_JS:
            break;
        case LIN_TEMPERATURE_RISE_SA:
            break;
        case LIN_DIAGNOSTIC:
            break;
        default:
            break;
    }
}

void Update_LIN_Data(void)
{
            LIN_OUTPUT_STATE_Data[0] = outputState;

            LIN_GET_TRIGGER_TYPE_Data[0] = triggerType;

            LIN_OVER_CURRENT_FAULT_Data[0] = overCurrentFault;

            LIN_UVLO_FAULT_Data[0] = uvloFault;

            LIN_OVER_TEMP_FAULT_Data[0] = overTempFault;

            LIN_ADC_VCC_SENSE_Data[0] = 0xff & adcVccSense_curr;
            LIN_ADC_VCC_SENSE_Data[1] = 0xff & (adcVccSense_curr >> 8);

            LIN_ADC_CURRENT_SENSE_UNCORRECTED_Data[0] = 0xff & adcISense_curr;
            LIN_ADC_CURRENT_SENSE_UNCORRECTED_Data[1] = 0xff & (adcISense_curr  >> 8);

            LIN_ADC_TEMP_SENSE_Data[0] = 0xff & adcTSense_curr;
            LIN_ADC_TEMP_SENSE_Data[1] = 0xff & (adcTSense_curr >> 8);

            LIN_ADC_CURRENT_SENSE_CORRECTED_Data[0] = 0xff & adcISense_corr;
            LIN_ADC_CURRENT_SENSE_CORRECTED_Data[1] = 0xff & (adcISense_corr >> 8);

            LIN_CURRENT_SENSE_OFFSET_Data[0] = 0xff & iSenseOffset;
            LIN_CURRENT_SENSE_OFFSET_Data[1] = 0xff & (iSenseOffset >> 8);

            LIN_AMBIENT_TEMPERATURE_Data[0] = 0xff & Tambient;
            LIN_AMBIENT_TEMPERATURE_Data[1] = 0xff & (Tambient >> 8);

            LIN_HEATSINK_TEMPERATURE_Data[0] = 0xff & Tsink;
            LIN_HEATSINK_TEMPERATURE_Data[1] = 0xff & (Tsink >> 8);

            LIN_JUNCTION_TEMPERATURE_Data[0] = 0xff & Tjunction;
            LIN_JUNCTION_TEMPERATURE_Data[1] = 0xff & (Tjunction >> 8);

            LIN_TEMPERATURE_RISE_JS_Data[0] = 0xff & Trise_js;
            LIN_TEMPERATURE_RISE_JS_Data[1] = 0xff & (Trise_js >> 8);

            LIN_TEMPERATURE_RISE_SA_Data[0] = 0xff & Trise_sa;
            LIN_TEMPERATURE_RISE_SA_Data[1] = 0xff & (Trise_sa >> 8);
            
            LIN_DIAGNOSTIC_Data[0] = 0xff & adcISense_corr;
            LIN_DIAGNOSTIC_Data[1] = 0xff & (adcISense_corr >> 8);
            LIN_DIAGNOSTIC_Data[2] = 0xff & Tambient;
            LIN_DIAGNOSTIC_Data[3] = 0xff & (Tambient >> 8);
            LIN_DIAGNOSTIC_Data[4] = 0xff & Tsink;
            LIN_DIAGNOSTIC_Data[5] = 0xff & (Tsink >> 8);
            LIN_DIAGNOSTIC_Data[6] = 0xff & Tjunction;
            LIN_DIAGNOSTIC_Data[7] = 0xff & (Tjunction >> 8);            
}