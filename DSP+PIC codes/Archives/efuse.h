/* 
 * File:   efuse.h
 * Author: C52935
 *
 * Created on October 27, 2021, 9:57 AM
 */

#ifndef EFUSE_H
#define	EFUSE_H

#ifdef	__cplusplus
extern "C" {
#endif

extern uint16_t ticks_1ms; // updated in timer0 ISR

// LIN configurable variables
extern uint16_t a1_coef;
extern uint8_t  b1_coef;
extern uint16_t current2counts_squared;
extern uint8_t  dac_i_hw_trip;
extern uint16_t factor_rdson_rthsa;
extern uint16_t factor_rdson_rthjs;
extern uint16_t isense_max;
extern uint8_t  reduced_drive_time;
extern uint16_t  tcc_sample_time;
extern uint8_t  triggerType;
extern uint8_t  tj_limit;

// LIN read-only variables
extern uint16_t adcVccSense_curr;
extern uint16_t adcISense_curr;
extern uint16_t adcTSense_curr;
extern uint16_t adcISense_corr;
extern uint16_t iSenseOffset;
extern uint8_t  outputState;
extern uint8_t  overCurrentFault;
extern uint8_t  overTempFault;
extern int16_t  Tambient;
extern int16_t  Tsink;
extern int16_t  Tjunction;
extern int16_t  Trise_sa;
extern int16_t  Trise_js;
extern uint8_t  uvloFault;

enum EFUSE_STATES {OUTPUT_OFF, OUTPUT_ON};

void CmdOutput(uint8_t);
void EFuse(void);
void EFuseInit(void);
int16_t GetAmbientTemperature(void);
void ProcessAnalogInputs(void);
void TCC_Curve(void);


#ifdef	__cplusplus
}
#endif

#endif	/* EFUSE_H */

