/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15345
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set VCCSENSE_ANA2 aliases
#define VCCSENSE_ANA2_TRIS                 TRISAbits.TRISA2
#define VCCSENSE_ANA2_LAT                  LATAbits.LATA2
#define VCCSENSE_ANA2_PORT                 PORTAbits.RA2
#define VCCSENSE_ANA2_WPU                  WPUAbits.WPUA2
#define VCCSENSE_ANA2_OD                   ODCONAbits.ODCA2
#define VCCSENSE_ANA2_ANS                  ANSELAbits.ANSA2
#define VCCSENSE_ANA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define VCCSENSE_ANA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define VCCSENSE_ANA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define VCCSENSE_ANA2_GetValue()           PORTAbits.RA2
#define VCCSENSE_ANA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define VCCSENSE_ANA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define VCCSENSE_ANA2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define VCCSENSE_ANA2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define VCCSENSE_ANA2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define VCCSENSE_ANA2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define VCCSENSE_ANA2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define VCCSENSE_ANA2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set HVSENSE aliases
#define HVSENSE_TRIS                 TRISAbits.TRISA4
#define HVSENSE_LAT                  LATAbits.LATA4
#define HVSENSE_PORT                 PORTAbits.RA4
#define HVSENSE_WPU                  WPUAbits.WPUA4
#define HVSENSE_OD                   ODCONAbits.ODCA4
#define HVSENSE_ANS                  ANSELAbits.ANSA4
#define HVSENSE_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define HVSENSE_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define HVSENSE_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define HVSENSE_GetValue()           PORTAbits.RA4
#define HVSENSE_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define HVSENSE_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define HVSENSE_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define HVSENSE_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define HVSENSE_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define HVSENSE_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define HVSENSE_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define HVSENSE_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set ISENSE_ANB4 aliases
#define ISENSE_ANB4_TRIS                 TRISBbits.TRISB4
#define ISENSE_ANB4_LAT                  LATBbits.LATB4
#define ISENSE_ANB4_PORT                 PORTBbits.RB4
#define ISENSE_ANB4_WPU                  WPUBbits.WPUB4
#define ISENSE_ANB4_OD                   ODCONBbits.ODCB4
#define ISENSE_ANB4_ANS                  ANSELBbits.ANSB4
#define ISENSE_ANB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define ISENSE_ANB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define ISENSE_ANB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define ISENSE_ANB4_GetValue()           PORTBbits.RB4
#define ISENSE_ANB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define ISENSE_ANB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define ISENSE_ANB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define ISENSE_ANB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define ISENSE_ANB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define ISENSE_ANB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define ISENSE_ANB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define ISENSE_ANB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set ISENSE_C2IN3 aliases
#define ISENSE_C2IN3_TRIS                 TRISCbits.TRISC3
#define ISENSE_C2IN3_LAT                  LATCbits.LATC3
#define ISENSE_C2IN3_PORT                 PORTCbits.RC3
#define ISENSE_C2IN3_WPU                  WPUCbits.WPUC3
#define ISENSE_C2IN3_OD                   ODCONCbits.ODCC3
#define ISENSE_C2IN3_ANS                  ANSELCbits.ANSC3
#define ISENSE_C2IN3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define ISENSE_C2IN3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define ISENSE_C2IN3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define ISENSE_C2IN3_GetValue()           PORTCbits.RC3
#define ISENSE_C2IN3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define ISENSE_C2IN3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define ISENSE_C2IN3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define ISENSE_C2IN3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define ISENSE_C2IN3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define ISENSE_C2IN3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define ISENSE_C2IN3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define ISENSE_C2IN3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set DRIVER_EN2 aliases
#define DRIVER_EN2_TRIS                 TRISCbits.TRISC6
#define DRIVER_EN2_LAT                  LATCbits.LATC6
#define DRIVER_EN2_PORT                 PORTCbits.RC6
#define DRIVER_EN2_WPU                  WPUCbits.WPUC6
#define DRIVER_EN2_OD                   ODCONCbits.ODCC6
#define DRIVER_EN2_ANS                  ANSELCbits.ANSC6
#define DRIVER_EN2_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define DRIVER_EN2_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define DRIVER_EN2_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define DRIVER_EN2_GetValue()           PORTCbits.RC6
#define DRIVER_EN2_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define DRIVER_EN2_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define DRIVER_EN2_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define DRIVER_EN2_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define DRIVER_EN2_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define DRIVER_EN2_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define DRIVER_EN2_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define DRIVER_EN2_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set DRIVER_EN1 aliases
#define DRIVER_EN1_TRIS                 TRISCbits.TRISC7
#define DRIVER_EN1_LAT                  LATCbits.LATC7
#define DRIVER_EN1_PORT                 PORTCbits.RC7
#define DRIVER_EN1_WPU                  WPUCbits.WPUC7
#define DRIVER_EN1_OD                   ODCONCbits.ODCC7
#define DRIVER_EN1_ANS                  ANSELCbits.ANSC7
#define DRIVER_EN1_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define DRIVER_EN1_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define DRIVER_EN1_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define DRIVER_EN1_GetValue()           PORTCbits.RC7
#define DRIVER_EN1_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define DRIVER_EN1_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define DRIVER_EN1_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define DRIVER_EN1_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define DRIVER_EN1_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define DRIVER_EN1_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define DRIVER_EN1_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define DRIVER_EN1_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/