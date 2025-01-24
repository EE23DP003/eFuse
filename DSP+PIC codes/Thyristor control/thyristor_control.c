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
    GPIO_writePin(myBoardLED0_GPIO, 1);
    GPIO_writePin(myBoardLED1_GPIO, 0);
    DEVICE_DELAY_US(7000);              //delay which is less than tripping time
    GPIO_writePin(EN1_M1, 0);           //bring the circuit back to normal current

    GPIO_writePin(myBoardLED0_GPIO, 0);
    GPIO_writePin(myBoardLED1_GPIO, 1);

    while (1);



}

//
//
// End of File
//


