#include "driverlib.h"
#include "device.h"
#include "board.h"



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


    GPIO_writePin(EN1_M1, 1);           //perform overcurrent
    DEVICE_DELAY_US(500);              //add required delay
    GPIO_writePin(EN1_M1, 0);           //perform overcurrent
    GPIO_writePin(EN2_M1, 1);           //perform shortcircuit
    DEVICE_DELAY_US(80);              //add required delay
    GPIO_writePin(EN2_M1, 0);           //perform shortcircuit


    while (1);                          //stop the code



}

//
//
// End of File
//


