#include "driverlib.h"
#include "device.h"
#include "board.h"

#define I_SQUARED_T_THRESHOLD 5  // I= 50A, t=1ms, 1pt= 20.14mA
#define CURRENT_SCALE ((float)0.02014)      // 1pt= 20.14mA for 2mOhms CSR, 40.28mA for 1mOhms CSR // (3.3V/4096)*(1A/40mV)
#define OVERCURRENT_TH 7     // 1pt= 20.14mA



uint16_t module1current = 0;
uint16_t module2current = 0;

uint16_t module1ADC = 0;
uint16_t module2ADC = 0;

uint16_t module1offset = 28;
uint16_t module2offset = 28;

float Overcurrent_Threshold = OVERCURRENT_TH / CURRENT_SCALE;

float i2t_accumulated1 = 0;
float i2t_accumulated2 = 0;

uint16_t i2t_threshold = I_SQUARED_T_THRESHOLD;
uint16_t overcurrent_duration = 0;
uint16_t timer_duration = 1;  // take the value from sysconfig(in ms)
volatile bool overcurrentDetected = false;
float temp1 = 0;
float temp2 = 0;
float temp3 = 0;
float temp4 = 0;
uint16_t current1=0;
uint16_t current2=0;

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

    GPIO_writePin(EN1_M1, 1);
    GPIO_writePin(EN2_M1, 0);

    while (1)
    {



        if (module1ADC > Overcurrent_Threshold)
        {
            if (!overcurrentDetected)
            { // Only start timer if newly detected
                overcurrentDetected = true;
                GPIO_writePin(myBoardLED0_GPIO, 1);
                GPIO_writePin(myBoardLED1_GPIO, 0);

                CPUTimer_startTimer(I2T_TIMER_0_BASE);
            }
        }
        else
        {
            overcurrentDetected = false; // Reset the flag
            i2t_accumulated1 = 0;
            CPUTimer_stopTimer(I2T_TIMER_0_BASE);
            CPUTimer_reloadTimerCounter(I2T_TIMER_0_BASE);
            overcurrent_duration = 0;
        }
    }

}

__interrupt void INT_I2T_TIMER_0_ISR(void)
{

    current1 = module1current-module1offset;  //correcting offset
    temp1 = current1 * current1;  // calculating i2 in points
    temp2 = 0.001 * temp1;      //scaling from ms to s

    i2t_accumulated1 += temp2 * CURRENT_SCALE * CURRENT_SCALE
            * overcurrent_duration; //converting from points to A2 and multiplying timer duration

    if ((i2t_accumulated1 >= i2t_threshold || module1current < Overcurrent_Threshold))
    {
        CPUTimer_stopTimer(I2T_TIMER_0_BASE);
        overcurrentDetected = false;

        if (i2t_accumulated1 >= i2t_threshold)
        {
            GPIO_writePin(EN1_M1, 0);
            GPIO_writePin(EN2_M1, 1);

            GPIO_writePin(31, 1);
            GPIO_writePin(34, 1);

            CPUTimer_stopTimer(I2T_TIMER_0_BASE);
            while (1)
                ;

        }
    }
    Interrupt_clearACKGroup(INT_I2T_TIMER_0_INTERRUPT_ACK_GROUP);
}

interrupt void INT_myADC1_1_ISR(void)
{

    // Read the ADC Result
    module1ADC = ADC_readResult(myADC1_RESULT_BASE, myADC1_SOC0);
    module1current = module1ADC;

    Interrupt_clearACKGroup(INT_myADC1_1_INTERRUPT_ACK_GROUP);
    ADC_clearInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1);
} // End of ADC ISR

//
//
// End of File
//


