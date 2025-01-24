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


#ifdef VARIANT_A
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    /*      Detection Method 1: Junction-Temperature Estimation constants         */
    #define A1_COEF                     65292   // Low pass filter coefficient, a1 (generated in Matlab)
    #define B1_COEF                     122     // Low pass filter coefficient, b0 and b1 are equal
    #define FACTOR_RDSON_RTHJS          979     // round(Rdsonmax*Rthjc*Rthcs*2^TEMP_RISE_SCALING_FACTOR*10
    #define FACTOR_RDSON_RTHSA          5492    // round(Rdsonmax/N*Rthsa*2^TEMP_RISE_SCALING_FACTOR*10
    #define NUM_DEVICES                 1       // number of MOSFETs in parallel
    #define TJ_LIMIT                    175     // max allowable junction temperature

    /*      Detection Method 2: Over-current (ADC-Based) Measurement constant     */
    #define ISENSE_MAX                  188     // 1 count = 0.1222A

    /*      Detection Method 3: Hardware short-Circuit Detection variable         */
    // 'dac_i_hw_trip' is defined in the LIN-configurable parameter definitions. 
    #define REDUCED_DRIVE_TIME          0       // 250ns resolution
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/

#elif VARIANT_B
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    /*      Detection Method 1: Junction-Temperature Estimation constants         */
    #define A1_COEF                     65326   // Low pass filter coefficient, a1 (generated in Matlab)
    #define B1_COEF                     105     // Low pass filter coefficient, b0 and b1 are equal
    #define FACTOR_RDSON_RTHJS          979     // round(Rdsonmax*Rthjc*Rthcs*2^TEMP_RISE_SCALING_FACTOR*10
    #define FACTOR_RDSON_RTHSA          1658    // round(Rdsonmax/N*Rthsa*2^TEMP_RISE_SCALING_FACTOR*10
    #define NUM_DEVICES                 2       // number of MOSFETs in parallel
    #define TJ_LIMIT                    175     // max allowable junction temperature

    /*      Detection Method 2: Over-current (ADC-Based) Measurement constant     */
    #define ISENSE_MAX                  376     // 1 count = 0.1222A

    /*      Detection Method 3: Hardware short-Circuit Detection variable         */
    // 'dac_i_hw_trip' is defined in the LIN-configurable parameter definitions. 
    #define REDUCED_DRIVE_TIME          0       // 250ns resolution
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/

#elif VARIANT_C
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    /*      Detection Method 1: Junction-Temperature Estimation constants         */
    #define A1_COEF                     65326   // Low pass filter coefficient, a1 (generated in Matlab)
    #define B1_COEF                     105     // Low pass filter coefficient, b0 and b1 are equal
    #define FACTOR_RDSON_RTHJS          421     // round(Rdsonmax*Rthjc*Rthcs*2^TEMP_RISE_SCALING_FACTOR*10
    #define FACTOR_RDSON_RTHSA          778     // round(Rdsonmax/N*Rthsa*2^TEMP_RISE_SCALING_FACTOR*10
    #define NUM_DEVICES                 2       // number of MOSFETs in parallel
    #define TJ_LIMIT                    175     // max allowable junction temperature

    /*      Detection Method 2: Over-current (ADC-Based) Measurement constant     */
    #define ISENSE_MAX                  44     // 1 count = 0.1222A

    /*      Detection Method 3: Hardware short-Circuit Detection variable         */
    // 'dac_i_hw_trip' is defined in the LIN-configurable parameter definitions. 
    #define REDUCED_DRIVE_TIME          0       // 250ns resolution
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/

#elif VARIANT_D
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    /*      Detection Method 1: Junction-Temperature Estimation constants         */
    #define A1_COEF                     65292   // Low pass filter coefficient, a1 (generated in Matlab)
    #define B1_COEF                     122     // Low pass filter coefficient, b0 and b1 are equal
    #define FACTOR_RDSON_RTHJS          1444    // round(Rdsonmax*Rthjc*Rthcs*2^TEMP_RISE_SCALING_FACTOR*10
    #define FACTOR_RDSON_RTHSA          8412    // round(Rdsonmax/N*Rthsa*2^TEMP_RISE_SCALING_FACTOR*10
    #define NUM_DEVICES                 1       // number of MOSFETs in parallel
    #define TJ_LIMIT                    175     // max allowable junction temperature

    /*      Detection Method 2: Over-current (ADC-Based) Measurement constant     */
    #define ISENSE_MAX                  155     // 1 count = 0.1222A

    /*      Detection Method 3: Hardware short-Circuit Detection variable         */
    // 'dac_i_hw_trip' is defined in the LIN-configurable parameter definitions. 
    #define REDUCED_DRIVE_TIME          0       // 250ns resolution
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/

#elif VARIANT_E
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    /*      Detection Method 1: Junction-Temperature Estimation constants         */
    #define A1_COEF                     65326   // Low pass filter coefficient, a1 (generated in Matlab)
    #define B1_COEF                     105     // Low pass filter coefficient, b0 and b1 are equal
    #define FACTOR_RDSON_RTHJS          1444    // round(Rdsonmax*Rthjc*Rthcs*2^TEMP_RISE_SCALING_FACTOR*10
    #define FACTOR_RDSON_RTHSA          2540    // round(Rdsonmax/N*Rthsa*2^TEMP_RISE_SCALING_FACTOR*10
    #define NUM_DEVICES                 2       // number of MOSFETs in parallel
    #define TJ_LIMIT                    175     // max allowable junction temperature

    /*      Detection Method 2: Over-current (ADC-Based) Measurement constant     */
    #define ISENSE_MAX                  311     // 1 count = 0.1222A

    /*      Detection Method 3: Hardware short-Circuit Detection variable         */
    // 'dac_i_hw_trip' is defined in the LIN-configurable parameter definitions. 
    #define REDUCED_DRIVE_TIME          0       // 250ns resolution
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/

#elif VARIANT_F
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/
    /*      Detection Method 1: Junction-Temperature Estimation constants         */
    #define A1_COEF                     65326   // Low pass filter coefficient, a1 (generated in Matlab)
    #define B1_COEF                     105     // Low pass filter coefficient, b0 and b1 are equal
    #define FACTOR_RDSON_RTHJS          787     // round(Rdsonmax*Rthjc*Rthcs*2^TEMP_RISE_SCALING_FACTOR*10
    #define FACTOR_RDSON_RTHSA          1473    // round(Rdsonmax/N*Rthsa*2^TEMP_RISE_SCALING_FACTOR*10
    #define NUM_DEVICES                 2       // number of MOSFETs in parallel
    #define TJ_LIMIT                    175     // max allowable junction temperature

    /*      Detection Method 2: Over-current (ADC-Based) Measurement constant     */
    #define ISENSE_MAX                  417     // 1 count = 0.1222A

    /*      Detection Method 3: Hardware short-Circuit Detection variable         */
    // 'dac_i_hw_trip' is defined in the LIN-configurable parameter definitions. 
    #define REDUCED_DRIVE_TIME          0       // 250ns resolution
    /******************************************************************************/
    /******************************************************************************/
    /******************************************************************************/

#endif





// TCC parameters
#define CURRENT2COUNTS_SQUARED      670     // round((0.002*20/5*(2^10-1))^2 * 10) current to counts squared and scaled
#define LPF_FACTOR                  16      // Low pass filter coefficient 2^16 scaling factor
#define TEMP_RISE_SCALING_FACTOR    10      // 2^10    

// Analog voltage and current sense limits
#define ISENSE_OFFSET_MAX           10      // maximum allowable ADC offset error to correct
#define ISHUNT_CURRENT_MAX          422     // max shunt current of 51.5A
#define VCCSENSE_MIN                372     // about 20V wrt HVGND

// Temperature sensor lookup table
#define TEMP_LUT_START              125     // LUT first entry
#define TEMP_LUT_END                -40     // LUT last entry
#define TEMP_LUT_STEP               -1      // LUT temperature step is -1C
#define TEMP_MAX_AMBIENT            115     // maximum ambient temperature
#define TEMP_SENSE_OORL             10      // temperature sensor out of range low, ADC counts
#define TEMP_SENSE_OORH             1013    // temperature sensor out of range high, ADC counts

// ADC & DAC delays
#define ACQ_US_DELAY                5       // ADC aquisition time
#define DAC_CMP2_US_DELAY           20      // DAC and comparator settling time
#define TCC_SAMPLE_TIME             1000    // 1ms resolution




//enum EFUSE_STATES {OUTPUT_OFF, OUTPUT_ON};
enum EFUSE_TRIGGER_TYPES {TRIGGER_EDGE, TRIGGER_TIMER_OVERFLOW};
enum HW_TRIP_CURRENT_THRESHOLDS {I_HW_TRIP_0A, I_HW_TRIP_33A, I_HW_TRIP_66A, I_HW_TRIP_99A, I_HW_TRIP_132A, I_HW_TRIP_165A, I_HW_TRIP_198A};
enum OCP_FAULT_STATES {NO_OVER_CURRENT_FAULT, SLOW_OVER_CURRENT_FAULT, FAST_OVER_CURRENT_FAULT, SHORT_CIRCUIT};
enum UVLO_FAULT_STATES {NO_UVLO_FAULT, UVLO_FAULT};
enum TEMP_FAULT_STATES {NO_TEMP_FAULT, TEMP_FAULT, TEMP_SENSOR_OORL, TEMP_SENSOR_OORH};


// Global Variables
uint16_t adcVccSense_curr = 0;
uint16_t adcVccSense_prev = 0;
uint16_t adcISense_corr = 0;
uint16_t adcISense_curr = 0;
uint16_t adcISense_OneMOSFET = 0;
uint16_t adcISense_prev = 0;
uint16_t adcTSense_curr = 0;
uint16_t adcTSense_prev = 0;
uint16_t iSenseOffset = 0;
uint8_t  outputState = OUTPUT_OFF;
uint8_t  overCurrentFault = NO_OVER_CURRENT_FAULT;
uint16_t ticks_1ms = 0;
uint8_t  triggerType = TRIGGER_EDGE;
uint8_t  uvloFault = NO_UVLO_FAULT;
uint8_t  overTempFault = NO_TEMP_FAULT;
int16_t  Tambient = 85;
int16_t  Tsink = 0;
int16_t  Tjunction = 0;
int16_t  Trise_sa = 0;
uint32_t Trise_filtered = 0;
int16_t  Trise_js = 0;
uint32_t Trise_raw_curr = 0;
uint32_t Trise_raw_prev = 0;


const uint16_t temperatureLUT[] = {
    104, 106, 108, 111, 113, 115,   // 125C to 120C
    118, 120, 123, 125, 128, 131, 133, 136, 139, 142,   // 119C to 110C
    145, 148, 151, 155, 158, 161, 165, 168, 172, 176,   // 109C to 100C
    179, 183, 187, 191, 195, 200, 204, 208, 213, 217,   // 99C to 90C
    222, 227, 232, 236, 241, 247, 252, 257, 263, 268,   // 89C to 80C
    274, 279, 285, 291, 297, 303, 310, 316, 322, 329,   // 79C to 70C
    336, 342, 349, 356, 363, 370, 377, 385, 392, 400,   // 69C to 60C
    407, 415, 423, 431, 439, 447, 455, 464, 472, 480,   // 59C to 50C
    489, 497, 506, 514, 523, 532, 540, 549, 558, 567,   // 49C to 40C
    575, 584, 593, 601, 610, 619, 628, 636, 645, 654,   // 39C to 30C
    662, 671, 679, 688, 696, 704, 712, 721, 729, 736,   // 29C to 20C
    744, 752, 760, 767, 775, 782, 789, 797, 804, 810,   // 19C to 10C
    817, 824, 830, 837, 843, 849, 855, 861, 867, 872,   // 9C to 0C
    878, 883, 888, 893, 898, 903, 908, 912, 917, 921,   // -1C to -10C
    925, 929, 933, 937, 941, 944, 948, 951, 954, 957,   // -11C to -20C
    960, 963, 966, 968, 971, 973, 976, 978, 980, 982,   // -21C to -30C
    984, 986, 988, 990, 992, 993, 995, 996, 998, 999    // -31C to -40C
}; // 125C, 124C, 123C ... -39C -40C, VDDHV=5V, Rpullup=4.7kOhms


// LIN-Configurable E-Fuse Parameters
uint16_t a1_coef = A1_COEF;
uint8_t  b1_coef = B1_COEF;
uint16_t current2counts_squared = CURRENT2COUNTS_SQUARED;
uint8_t  dac_i_hw_trip = I_HW_TRIP_33A;
uint16_t factor_rdson_rthjs = FACTOR_RDSON_RTHJS;
uint16_t factor_rdson_rthsa = FACTOR_RDSON_RTHSA;
uint16_t isense_max = ISENSE_MAX;
uint8_t  reduced_drive_time = REDUCED_DRIVE_TIME;
uint16_t  tcc_sample_time = TCC_SAMPLE_TIME;
uint8_t  tj_limit = TJ_LIMIT;


void EFuseInit(void)
{
    CmdOutput(OUTPUT_OFF); // never enable output in this function VCC is still ramping up in voltage

    // Enable over-current protection (OCP)
    CM2CON0bits.C2EN = 1;       // Enable comparator 2
    CLC1GLS1bits.LC1G2D2T = 1;  // Connect OCP comparator 2 output to CLC gate 1 input
    PIR2bits.C2IF = 0;          // Clearing comparator 2 IF flag before enabling the interrupt.

    DAC1CON1bits.DAC1R = dac_i_hw_trip;   // Setup DAC comparator reference
    __delay_us(DAC_CMP2_US_DELAY);
    
    // Set periodic timer and clear interrupt flags
    TMR0_Reload();
    PIR0bits.TMR0IF = 0;
    PIR5bits.CLC2IF = 0;
    PIR2bits.C1IF = 0;
    PIR2bits.C2IF = 0;

    ticks_1ms = 0;

    triggerType = TRIGGER_EDGE; // edge on comparator 2 output triggers shutdown    
}

void EFuse(void) 
{
    // Check if timer 1 overflowed, indicates output turned off
    if(PIR4bits.TMR1IF && (outputState == OUTPUT_ON))
    {
       overCurrentFault = SHORT_CIRCUIT;
       CmdOutput(OUTPUT_OFF);
       PIR4bits.TMR1IF = 0;  // Clear timer1 interrupt flag
    }

    if(ticks_1ms >= tcc_sample_time)
    {
        ticks_1ms = 0;

        // Reset timer 2
        if(CLCDATAbits.MLC4OUT && (outputState == OUTPUT_ON)) // checks if T2TMR==T2PR
        {
            // clock timer 2 source, CLC3OUT, to clear T2TMR
            CLC3GLS1 = 0x00;
            T2TMR = 0x00;
            CLC3POL = 0x00;
            CLC3POL = 0x03;
            CLC3POL = 0x00;
            CLC3GLS1 = 0x08;
        }
        Tambient=GetAmbientTemperature();
        if(Tambient >= TEMP_MAX_AMBIENT) // high ambient temperature
        {
            Tambient = TEMP_MAX_AMBIENT;
            overTempFault = TEMP_FAULT;
//            CmdOutput(OUTPUT_OFF);
        }
        else
        {
            if((adcISense_curr >= iSenseOffset) && (iSenseOffset < ISENSE_OFFSET_MAX)) // check for ADC offset error, only correct up to ISENSE_OFFSET_MAX counts
            {
                adcISense_corr = adcISense_curr - iSenseOffset; // corrected ADC counts
            }
            else
            {
                adcISense_corr = adcISense_curr;
            }
            adcISense_OneMOSFET = adcISense_corr / NUM_DEVICES; // divide current between the devices, assume even current sharing
            TCC_Curve(); // Time-Current Characteristic Curve (I2T curve)
            if(Tjunction >= tj_limit)
            {
                overCurrentFault = SLOW_OVER_CURRENT_FAULT;
//                CmdOutput(OUTPUT_OFF);
            }
        }
        Update_LIN_Data();            
    }
}


void ProcessAnalogInputs(void)
{
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
    __delay_us(ACQ_US_DELAY);  // discharge hold capacitor
    
    if (isense_max > ISHUNT_CURRENT_MAX) // limit over-current threshold to shunt resistor capability
    {
        isense_max = ISHUNT_CURRENT_MAX;
    }
    // Check for over current
    if((adcISense_prev > isense_max) && (adcISense_curr > isense_max) && (outputState == OUTPUT_ON))
    {
        overCurrentFault = FAST_OVER_CURRENT_FAULT;
        CmdOutput(OUTPUT_OFF);
    }


    if(ticks_1ms) // check VCC voltage every 1ms interrupt except the very first (ticks_1ms=0), in which case check the temperature instead
    {
        adcVccSense_prev = adcVccSense_curr;
        adcVccSense_curr = ADC_GetConversion(VCCSENSE_ANA2);
        ADC_SelectChannel(channel_AVSS);
        __delay_us(ACQ_US_DELAY);  // discharge hold capacitor
        
        // Check for VCC under-voltage
        if((adcVccSense_prev < VCCSENSE_MIN) && (adcVccSense_curr < VCCSENSE_MIN) && (outputState == OUTPUT_ON))
        {
            uvloFault = UVLO_FAULT;
            CmdOutput(OUTPUT_OFF);
        }
    }
    else
    {
        adcTSense_prev = adcTSense_curr;
        adcTSense_curr = ADC_GetConversion(TSENSE_ANC4);
        ADC_SelectChannel(channel_AVSS);
        
        if((adcTSense_prev < TEMP_SENSE_OORL) && (adcTSense_curr < TEMP_SENSE_OORL)) // if less than specified counts then sensor shorted to HVGND
        {
            overTempFault = TEMP_SENSOR_OORL; // out of range low fault, short to HVGND
//            CmdOutput(OUTPUT_OFF);
        }
        else if((adcTSense_prev > TEMP_SENSE_OORH) && (adcTSense_curr > TEMP_SENSE_OORH)) // if within specified counts on the high end, then short to VDDHV
        {
            overTempFault = TEMP_SENSOR_OORH; // out of range high fault, short to VDDHV
            CmdOutput(OUTPUT_OFF);
        }
    }
}


void CmdOutput(uint8_t enable)
{
    TMR2_Stop();
    
    // CLC1 latch output triggers timer - single edge on CMP2
    CLC1POLbits.LC1G4POL = 0;   // CLC1 gate 4 output not inverted
    CLC1GLS3bits.LC1G4D3N = 0;  // disconnect timer2 overflow signal
    CLC1GLS3bits.LC1G4D4T = 0;  // disconnect CLC2OUT signal

    // CLC1 latch output triggers timer - single edge on CMP2
    //T1GE enabled; T1GTM disabled; T1GPOL low; T1GGO done; T1GSPM disabled; 
    T1GCON = 0x80;

    //GSS CLC1OUT; 
    T1GATE = 0x0D;

    CLC3CONbits.EN = 0;

    // Command reduced gate drive
    CLC1POLbits.LC1G2POL = 1;  // Sets CLC1 gate 1 output
    CLC1POLbits.LC1G2POL = 0;  // Clears CLC1 gate 1 output        
    
    __delay_us(1);  // Reduced gate drive duration

    // Trigger CLC2 latch to set RC6 high (EN2 output)
    CLC2POLbits.LC2G2POL = 1;  // Sets CLC2 gate 1 output
    CLC2POLbits.LC2G2POL = 0;  // Clears CLC2 gate 1 output        
    
    outputState = OUTPUT_OFF;
    
    // Command output on
    if (enable)
    {
        overCurrentFault = NO_OVER_CURRENT_FAULT;
        uvloFault = NO_UVLO_FAULT;
        overTempFault = NO_TEMP_FAULT;
        
        DRIVER_EN1_SetDigitalInput();

        // Toggle CLC1 latch reset input to enable DRIVER_EN1 output              
        CLC1CONbits.LC1EN = 1;          // Enable CLC1
        CLC1POLbits.LC1G4POL = 0;       // Clears CLC1 gate 3 output
        CLC1POLbits.LC1G3POL = 0;       // Clears CLC1 gate 2 output
        CLC1POLbits.LC1G3POL = 1;       // Sets CLC1 gate 2 output
        CLC1POLbits.LC1G3POL = 0;       // Clears CLC1 gate 2 output        
        CLC1POLbits.LC1POL = 1;         // Enable CLC1 output inverter
        
        // Toggle CLC2 latch reset input to disable DRIVER_EN2 output
        CLC2POLbits.LC2G4POL = 0;       // Clears CLC2 gate 3 output
        CLC2POLbits.LC2G3POL = 0;       // Clears CLC2 gate 2 output
        CLC2POLbits.LC2G3POL = 1;       // Sets CLC2 gate 2 output
        CLC2POLbits.LC2G3POL = 0;       // Clears CLC2 gate 2 output        
        
        if(triggerType == TRIGGER_TIMER_OVERFLOW)
        {
            // Comparator 2 increments timer (timer periodically reset every in main loop)
            // This option enables riding through transient event
            CLC1POLbits.LC1G4POL = 1;   // CLC1 gate 4 output inverted
            CLC1GLS3bits.LC1G4D3N = 1;  // connect and invert timer2 overflow signal
            CLC1GLS3bits.LC1G4D4T = 1;  // connect CLC2OUT signal

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
        TMR1_WriteTimer( 0xffff - reduced_drive_time );
        PIR4bits.TMR1IF = 0;
        TMR1_StartTimer();      
        
        iSenseOffset = adcISense_curr;
        outputState = OUTPUT_ON;        
        DRIVER_EN1_SetDigitalOutput();
    }
}


void TCC_Curve(void)
{
    Trise_raw_prev = Trise_raw_curr;
    Trise_raw_curr = (uint32_t) ((((uint64_t) adcISense_corr * (uint64_t) adcISense_corr) * factor_rdson_rthsa) >> TEMP_RISE_SCALING_FACTOR);
    Trise_filtered = (uint32_t) ((uint64_t) a1_coef * Trise_filtered + (uint32_t) b1_coef * (Trise_raw_prev + Trise_raw_curr)) >> LPF_FACTOR;

    Trise_sa = (int16_t) (Trise_filtered / current2counts_squared);
    Tsink = Tambient + Trise_sa;

    Trise_js = (int16_t) (((((uint32_t) adcISense_OneMOSFET * (uint32_t) adcISense_OneMOSFET) * factor_rdson_rthjs) >> TEMP_RISE_SCALING_FACTOR) / current2counts_squared);
    Tjunction = Tsink + Trise_js;
}


int16_t GetAmbientTemperature(void)
{
    uint8_t i = 0;
    uint16_t adcTemp = 0;
    int16_t temperature = 0;
    
    adcTemp = adcTSense_prev;   
    if (adcTSense_curr > adcTSense_prev) // use lower temperature of two readings, consider replacing with digital LPF
    {
        adcTemp = adcTSense_curr;           
    }
    
    temperature = TEMP_LUT_START;   // in units of deg C
    i = 0;
    while(temperature > TEMP_LUT_END) 
    {
        if(adcTemp <= temperatureLUT[i])   // if adc counts (sensor voltage) is less than or equal to LUT entry
        {
            return temperature;    
        }
        else
        {
            temperature = temperature + TEMP_LUT_STEP;
            i++;
        }
    }
    
    return temperature;    
}
