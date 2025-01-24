/* 
 * File:   efuse.c
 * Author: C52935
 *
 * Created on October 27, 2021, 9:57 AM
 */


#include <xc.h>
#include <stdio.h>
#include "efuse.h"
#include "mcc_generated_files/mcc.h"


#define NUM_DEVICES                 2       // number of MOSFETs in parallel

/*      Detection Method 2: Over-current (ADC-Based) Measurement constant     */
#define ISENSE_MAX                 98     // 1 count = 0.244A       //User-Changed

/*      Detection Method 3: Hardware short-Circuit Detection variable         */
// 'dac_i_hw_trip' is defined in the LIN-configurable parameter definitions. 
#define REDUCED_DRIVE_TIME          0       // 250ns resolution







// Analog voltage and current sense limits
//Last measured offset = 12mV 
#define ISENSE_OFFSET_MAX           2      // maximum allowable ADC offset error to correct // User-Changed 
#define ISHUNT_CURRENT_MAX          114     // max shunt current of 92.1A //User-Changed
#define VCCSENSE_MIN                400     // about 20V wrt HVGND for power shutdown protection //User-Changed
#define HVSENSE_UVLO_TH             507    // 507 for 300V, 591 for 350V
#define HVSENSE_OVLO_TH             760    // 676 for 400V, 760 for 450V
#define MIN_CURR_UVLO               5    // 0.244A for 1pt

// ADC & DAC delays
#define ACQ_US_DELAY                5       // ADC aquisition time
#define DAC_CMP2_US_DELAY           20      // DAC and comparator settling time
#define TCC_SAMPLE_TIME             1000    // 1ms resolution




//enum EFUSE_STATES {OUTPUT_OFF, OUTPUT_ON};

enum EFUSE_TRIGGER_TYPES {
    TRIGGER_EDGE, TRIGGER_TIMER_OVERFLOW
};

enum HW_TRIP_CURRENT_THRESHOLDS {
    I_HW_TRIP_0A, I_HW_TRIP_33A, I_HW_TRIP_66A, I_HW_TRIP_99A, I_HW_TRIP_132A, I_HW_TRIP_165A, I_HW_TRIP_198A
};

enum OCP_FAULT_STATES {
    NO_OVER_CURRENT_FAULT, SLOW_OVER_CURRENT_FAULT, FAST_OVER_CURRENT_FAULT, SHORT_CIRCUIT
};

enum UVLO_FAULT_STATES {
    NO_UVLO_FAULT, UVLO_FAULT
};



// Global Variables
uint16_t adcVccSense_curr = 0;
uint16_t adcVccSense_prev = 0;
uint16_t adcISense_corr = 0;
uint16_t adcISense_curr = 0;
uint16_t adcISense_OneMOSFET = 0;
uint16_t adcISense_prev = 0;
uint16_t iSenseOffset = 0;
uint8_t outputState = OUTPUT_OFF;
uint8_t overCurrentFault = NO_OVER_CURRENT_FAULT;
uint16_t ticks_1ms = 0;
uint8_t triggerType = TRIGGER_EDGE;
uint16_t adcHVsense = 0;




// LIN-Configurable E-Fuse Parameters
uint8_t dac_i_hw_trip = I_HW_TRIP_33A;
uint16_t isense_max = ISENSE_MAX;
uint8_t reduced_drive_time = REDUCED_DRIVE_TIME;
uint16_t tcc_sample_time = TCC_SAMPLE_TIME;

void EFuseInit(void) {
    CmdOutput(OUTPUT_OFF); // never enable output in this function VCC is still ramping up in voltage

    // Enable over-current protection (OCP)
    TMR0_Reload();
    PIR0bits.TMR0IF = 0;
    CM2CON0bits.C2EN = 1; // Enable comparator 2
    CLC1GLS1bits.LC1G2D2T = 1; // Connect OCP comparator 2 output to CLC gate 1 input
    PIR2bits.C2IF = 0; // Clearing comparator 2 IF flag before enabling the interrupt.

    DAC1CON1bits.DAC1R = dac_i_hw_trip; // Setup DAC comparator reference
    __delay_us(DAC_CMP2_US_DELAY);

    // Set periodic timer and clear interrupt flags
    PIR5bits.CLC2IF = 0;
    PIR2bits.C1IF = 0;
    PIR2bits.C2IF = 0;

    ticks_1ms = 0;

    triggerType = TRIGGER_EDGE; // edge on comparator 2 output triggers shutdown    
}

void EFuse(void) {
    // Check if timer 1 overflowed, indicates output turned off
    if (PIR4bits.TMR1IF && (outputState == OUTPUT_ON)) {
        CmdOutput(OUTPUT_OFF);
        PIR4bits.TMR1IF = 0; // Clear timer1 interrupt flag
    }

    if (ticks_1ms >= tcc_sample_time) {
        ticks_1ms = 0;

        // Reset timer 2
        if (CLCDATAbits.MLC4OUT && (outputState == OUTPUT_ON)) // checks if T2TMR==T2PR
        {
            // clock timer 2 source, CLC3OUT, to clear T2TMR
            CLC3GLS1 = 0x00;
            T2TMR = 0x00;
            CLC3POL = 0x00;
            CLC3POL = 0x03;
            CLC3POL = 0x00;
            CLC3GLS1 = 0x08;
        }

        if ((adcISense_curr >= iSenseOffset) && (iSenseOffset < ISENSE_OFFSET_MAX)) // check for ADC offset error, only correct up to ISENSE_OFFSET_MAX counts
        {
            adcISense_corr = adcISense_curr - iSenseOffset; // corrected ADC counts
        } else {
            adcISense_corr = adcISense_curr;
        }
        adcISense_OneMOSFET = adcISense_corr / NUM_DEVICES; // divide current between the devices, assume even current sharing

    }
}

void ProcessAnalogInputs(void) {
    /* ADC Channels
    VCCSENSE_ANA2 =  0x2,
    ISENSE_ANB4 =  0xC,
    TSENSE_ANC4 =  0x14,
    channel_AVSS =  0x3B,
    channel_Temp =  0x3C,
    channel_DAC1 =  0x3D,
    channel_FVR_BUF1 =  0x3E,
    channel_FVR_BUF2 =  0x3F
     */

    adcISense_prev = adcISense_curr;
    adcISense_curr = ADC_GetConversion(ISENSE_ANB4);
    ADC_SelectChannel(channel_AVSS);
    __delay_us(ACQ_US_DELAY); // discharge hold capacitor

    if (isense_max > ISHUNT_CURRENT_MAX) // limit over-current threshold to shunt resistor capability
    {
        isense_max = ISHUNT_CURRENT_MAX;
    }
    // Check for over current
    if ((adcISense_prev > isense_max) && (adcISense_curr > isense_max) && (outputState == OUTPUT_ON)) {
        CmdOutput(OUTPUT_OFF);
    }




    if (ticks_1ms) // check VCC voltage every 1ms interrupt except the very first (ticks_1ms=0), in which case check the temperature instead
    {
        adcVccSense_prev = adcVccSense_curr;
        adcVccSense_curr = ADC_GetConversion(VCCSENSE_ANA2);
        ADC_SelectChannel(channel_AVSS);
        __delay_us(ACQ_US_DELAY); // discharge hold capacitor

        // Check for VCC under-voltage
        if ((adcVccSense_prev < VCCSENSE_MIN) && (adcVccSense_curr < VCCSENSE_MIN) && (outputState == OUTPUT_ON)) {
            CmdOutput(OUTPUT_OFF);
        }

//        adcHVsense = ADC_GetConversion(HVSENSE);
//        ADC_SelectChannel(channel_AVSS);
//        __delay_us(ACQ_US_DELAY); // discharge hold capacitor
//
//        // Check for UVLO on HV line
//        if ((adcHVsense < HVSENSE_UVLO_TH) && (outputState == OUTPUT_ON) && (adcISense_curr > MIN_CURR_UVLO)) {
//            CmdOutput(OUTPUT_OFF);
//        }
//        
//        // Check for OVLO on HV line
//        if ((adcHVsense > HVSENSE_OVLO_TH) && (outputState == OUTPUT_ON) && (adcISense_curr > MIN_CURR_UVLO)) {
//            CmdOutput(OUTPUT_OFF);
//        }
    }
}

void CmdOutput(uint8_t enable) {
    TMR2_Stop();

    // CLC1 latch output triggers timer - single edge on CMP2
    CLC1POLbits.LC1G4POL = 0; // CLC1 gate 4 output not inverted
    CLC1GLS3bits.LC1G4D3N = 0; // disconnect timer2 overflow signal
    CLC1GLS3bits.LC1G4D4T = 0; // disconnect CLC2OUT signal

    // CLC1 latch output triggers timer - single edge on CMP2
    //T1GE enabled; T1GTM disabled; T1GPOL low; T1GGO done; T1GSPM disabled; 
    T1GCON = 0x80;

    //GSS CLC1OUT; 
    T1GATE = 0x0D;

    CLC3CONbits.EN = 0;

    // Command reduced gate drive
    CLC1POLbits.LC1G2POL = 1; // Sets CLC1 gate 1 output
    CLC1POLbits.LC1G2POL = 0; // Clears CLC1 gate 1 output        

    __delay_us(1); // Reduced gate drive duration

    // Trigger CLC2 latch to set RC6 high (EN2 output)
    CLC2POLbits.LC2G2POL = 1; // Sets CLC2 gate 1 output
    CLC2POLbits.LC2G2POL = 0; // Clears CLC2 gate 1 output        

    outputState = OUTPUT_OFF;

    // Command output on
    if (enable) {

        DRIVER_EN1_SetDigitalInput();

        // Toggle CLC1 latch reset input to enable DRIVER_EN1 output              
        CLC1CONbits.LC1EN = 1; // Enable CLC1
        CLC1POLbits.LC1G4POL = 0; // Clears CLC1 gate 3 output
        CLC1POLbits.LC1G3POL = 0; // Clears CLC1 gate 2 output
        CLC1POLbits.LC1G3POL = 1; // Sets CLC1 gate 2 output
        CLC1POLbits.LC1G3POL = 0; // Clears CLC1 gate 2 output        
        CLC1POLbits.LC1POL = 1; // Enable CLC1 output inverter

        // Toggle CLC2 latch reset input to disable DRIVER_EN2 output
        CLC2POLbits.LC2G4POL = 0; // Clears CLC2 gate 3 output
        CLC2POLbits.LC2G3POL = 0; // Clears CLC2 gate 2 output
        CLC2POLbits.LC2G3POL = 1; // Sets CLC2 gate 2 output
        CLC2POLbits.LC2G3POL = 0; // Clears CLC2 gate 2 output        

        if (triggerType == TRIGGER_TIMER_OVERFLOW) {
            // Comparator 2 increments timer (timer periodically reset every in main loop)
            // This option enables riding through transient event
            CLC1POLbits.LC1G4POL = 1; // CLC1 gate 4 output inverted
            CLC1GLS3bits.LC1G4D3N = 1; // connect and invert timer2 overflow signal
            CLC1GLS3bits.LC1G4D4T = 1; // connect CLC2OUT signal

            //T1GE enabled; T1GTM disabled; T1GPOL high; T1GGO done; T1GSPM disabled; 
            T1GCON = 0xC0;

            //GSS CMP2OUT; 
            T1GATE = 0x0B;

            TMR2_Initialize();
            TMR2_Start();

            CLC3CONbits.EN = 1;
        }

        // Setup timer before enabling output
        TMR1_StopTimer();
        TMR1_WriteTimer(0xffff - reduced_drive_time);
        PIR4bits.TMR1IF = 0;
        TMR1_StartTimer();

        iSenseOffset = adcISense_curr;
        outputState = OUTPUT_ON;
        DRIVER_EN1_SetDigitalOutput();
    }
}