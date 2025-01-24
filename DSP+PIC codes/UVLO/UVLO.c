#include "driverlib.h"
#include "device.h"
#include "board.h"

#define UVLO_THRESHOLD 268  //in Volts

float uvlo_threshold_pts = UVLO_THRESHOLD * 10.24;
uint16_t module1ADC = 0;
uint16_t module1offset = 28;

//
// Main
//
void main(void)
{
    // Device Initialization
    Device_init();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    Board_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        if (module1ADC > 4000)
        {
            GPIO_writePin(EN1_M1, 1);
            GPIO_writePin(EN2_M1, 0);
            break;
        }
    }

    while(1)
    {
        if (module1ADC < uvlo_threshold_pts)
        {
            GPIO_writePin(myBoardLED0_GPIO, 1);
            GPIO_writePin(myBoardLED1_GPIO, 0);
            GPIO_writePin(EN1_M1, 0);
            GPIO_writePin(EN2_M1, 1);
            while(1);
        }
    }



}

interrupt void INT_myADC1_1_ISR(void)
{

    // Read the ADC Result
    module1ADC = ADC_readResult(myADC1_RESULT_BASE, myADC1_SOC0);

    Interrupt_clearACKGroup(INT_myADC1_1_INTERRUPT_ACK_GROUP);
    ADC_clearInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1);
} // End of ADC ISR

//
//
// End of File
//

