/* 
 * File:   HardwareProfile.h
 * Author: Calvin
 *
 * Created on 2015?3?16?, ?? 6:13
 */

#ifndef HARDWAREPROFILE_H
#define	HARDWAREPROFILE_H

#define _XTAL_FREQ 8000000   //Fosc=8MHz
#define	LCM_RST     PORTBbits.RB7
#define	LCM_CE      PORTBbits.RB4
#define	LCM_DC      PORTBbits.RB5

#define LED1 PORTCbits.RC0
#define LED2 PORTCbits.RC1
#define LED3 PORTCbits.RC2
#define LED4 PORTCbits.RC3
#define LED5 PORTCbits.RC4
#define LED6 PORTCbits.RC5
#define LED7 PORTCbits.RC6

/*
#define sensor0 RA0
#define sensor1 RA1
#define sensor2 RA2
#define sensor3 RA4
#define ref0 RA2
#define ref1 RA4
#define ref2 RA0
#define ref3 RA1
*/

/*
#define sensor0_TRIS    TRISAbits.TRISA0    //RA0
#define sensor1_TRIS    TRISAbits.TRISA1    //RA1
#define sensor2_TRIS    TRISAbits.TRISA2    //RA2
#define sensor3_TRIS    TRISAbits.TRISA4    //RA4
#define ADC_to_Sensor0 0b10000001    //RA0
#define ADC_to_Sensor1 0b10000101    //RA1
#define ADC_to_Sensor2 0b10001001    //RA2
#define ADC_to_Sensor3 0b10001101    //RA4
#define ADC_to_ref0 ADC_to_Sensor2
#define ADC_to_ref1 ADC_to_Sensor3
#define ADC_to_ref2 ADC_to_Sensor0
#define ADC_to_ref3 ADC_to_Sensor1
*/

#endif	/* HARDWAREPROFILE_H */
