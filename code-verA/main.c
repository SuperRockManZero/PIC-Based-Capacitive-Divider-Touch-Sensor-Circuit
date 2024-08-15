/* 
 * File:   main.c
 * Author: Calvin
 *
 * Created on 2015?3?16?, ?? 5:48
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "HardwareProfile.h"
#include "LCM.h"
#include "pattern.h"
/***/
void init_system(void);
void init_LCM(void);
void init_CVD(void);
unsigned int CVD(unsigned char);
void display(unsigned char);
void LCM_pattern(char,char,char);
void LCM_clear(void);
signed char WriteSPI(unsigned char);
void LED(unsigned char,unsigned char);
/***/
unsigned int CVD_th[4];
const unsigned char scan_sequence[4][5] =             // sensor_low_ref_high, sensor_high_ref_low, sensor_input, ref_ADC, sensor_ADC
{
    { 0x04, 0x01, 0x09, 0x89, 0x81},	//for sensor0
    { 0x10, 0x02, 0x0A, 0x8D, 0x85},	//for sensor1
    { 0x01, 0x04, 0x0C, 0x81, 0x89},	//for sensor2
    { 0x02, 0x10, 0x18, 0x85, 0x8D}         //for sensor3
};
/***/
void main(void)
{
    unsigned char CVD_status;     //0:CVD_res<CVD_th, 1:CVD>CVD_th
    unsigned char CVD_old_status[]={0,0,0,0}; //last time CVD_status
    unsigned char sensor=0;
    unsigned char tmr0_counter=0;
    init_system();
    init_LCM();
    init_CVD();
    for(unsigned char i=0;i<4;i++)
    {
        LCM_pattern(0,i,((unsigned char)(CVD_th[i]>>12)) & 0x0F);
        LCM_pattern(6,i,((unsigned char)(CVD_th[i]>>8)) & 0x0F);
        LCM_pattern(12,i,((unsigned char)(CVD_th[i]>>4)) & 0x0F);
        LCM_pattern(18,i,((unsigned char) CVD_th[i]) & 0x0F);
    }
    while(1)
    {
        if(CVD(sensor)>CVD_th[sensor])      CVD_status=1;
        else                            CVD_status=0;
        if (CVD_status != CVD_old_status[sensor])
        {
            if(INTCONbits.T0IF==1)
            {
                INTCONbits.T0IF=0;
                tmr0_counter++;
            }
            if(tmr0_counter > 2)           //debounce time = 1~2msec
            {
                CVD_old_status[sensor] = CVD_status;
                tmr0_counter = 0;
            }
        }
        else
        {
            tmr0_counter = 0;
            sensor++;
            if(sensor>3)                sensor=0;
        }
        if(CVD_old_status[sensor]==0)   LED(sensor,0);
        else                            LED(sensor,1);
//        display(CVD_old_status[sensor]);
    }
}
void init_CVD(void)
{
    unsigned int CVD_res[4];
    unsigned long CVD_avg[4]={0,0,0,0};
    unsigned int  CVD_max[4]={0,0,0,0};
    for(unsigned char i=0;i<128;i++)
    {
        for(unsigned char j=0; j<4;j++)
        {
            CVD_res[j]=CVD(j);
            CVD_avg[j] += CVD_res[j];
            if (CVD_res[j] > CVD_max[j])    CVD_max[j] = CVD_res[j];
        }
    }
    for(unsigned char j=0; j<4;j++)
    {
        CVD_avg[j] = CVD_avg[j]>>7;     //CVD_avg=CVD_avg/128
        CVD_th[j] = ((CVD_max[j] - CVD_avg[j])>>1) + CVD_max[j];       //CVD_th = (CVD_amx-CVD_avg)*1.5+CVD_avg
    }
}
unsigned int CVD(unsigned char sensor)
{
    unsigned int CVD_A;
    unsigned int CVD_B;
//    unsigned int CVD_res;
    unsigned char sensor_low_ref_high = scan_sequence[sensor][0];   //sensor_pin to low and ref_pin to high
    unsigned char sensor_high_ref_low = scan_sequence[sensor][1];   //sensor_pin to high and ref_pin to low
    unsigned char sensor_input = scan_sequence[sensor][2];          //sensor_pin as input
    unsigned char ref_ADC = scan_sequence[sensor][3];               //ref_pin to ADC
    unsigned char sensor_ADC = scan_sequence[sensor][4];            //sensor_pin to ADC
    //CVD_A
    PORTA=sensor_low_ref_high;  //sensor_pin to low and ref_pin to high
    ADCON0=ref_ADC;             //ref_pin to ADC
    NOP();                      //delay time for charging
    NOP();
    NOP();
    TRISA=sensor_input;         //sensor_pin as input
    ADCON0=sensor_ADC;          //sensor_pin to ADC
    NOP();                      //delay time for capactors balance
    ADCON0bits.GO_nDONE=1;      //ADC to go
    TRISA=0b00001000;           //all sensor_pin / ref_pin as output
    PORTA=0;                    //all sensor_pin / ref_pin to low
    while(ADCON0bits.GO_nDONE);
    CVD_A= (((unsigned int)ADRESH)<<8)|(ADRESL);
    //CVD_B
    PORTA=sensor_high_ref_low;  //sensor_pin to high and ref_pin to low
    ADCON0=ref_ADC;             //ref_pin to ADC
    NOP();                      //delay time for charging
    NOP();
    NOP();
    TRISA=sensor_input;         //sensor_pin as input
    ADCON0=sensor_ADC;          //sensor_pin to ADC
    NOP();                      //delay time for capactors balance
    ADCON0bits.GO_nDONE=1;      //ADC to go
    TRISA=0b00001000;           //all sensor_pin / ref_pin as output
    PORTA=0;                    //all sensor_pin / ref_pin to low
    while(ADCON0bits.GO_nDONE);
    CVD_B= (((unsigned int)ADRESH)<<8)|(ADRESL);
//CVD_res
//    CVD_res = (CVD_B+1024) - CVD_A;
//    return (CVD_res);
    return ((CVD_B+1024) - CVD_A);
}
/*
 void display(unsigned char CVD_old_status)
{
    unsigned char ID;
    for(unsigned char i=0;i<4;i++)
    {
        ID = ((unsigned char)(CVD_th[i]>>12)) & 0x0F;
        LCM_pattern(0,i,ID);
        ID = ((unsigned char)(CVD_th[i]>>8)) & 0x0F;
        LCM_pattern(6,i,ID);
        ID = ((unsigned char)(CVD_th[i]>>4)) & 0x0F;
        LCM_pattern(12,i,ID);
        ID = ((unsigned char) CVD_th[i]) & 0x0F;
        LCM_pattern(18,i,ID);
    }
    if ((CVD_old_status&0x01) != 0)     ID = 1;
    else                                ID = 0;
    LCM_pattern(30,0,ID);
    if ((CVD_old_status&0x02) != 0)     ID = 1;
    else                                ID = 0;
    LCM_pattern(30,1,ID);
    if ((CVD_old_status&0x04) != 0)     ID = 1;
    else                                ID = 0;
    LCM_pattern(30,2,ID);
    if ((CVD_old_status&0x10) != 0)     ID = 1;
    else                                ID = 0;
    LCM_pattern(30,3,ID);
}
*/
void init_system(void)
{
//Initial Watch Dog and OSC
    WDTCON=0x00;            //WDT off
    OSCCON=0b01110001;       //Internal Oscillator 8MHz
//Initial OPTION and Timer
    OPTION_REG=0b00000010;   //TMR0 in 1:8 Prescale
    T1CON=0x00;             //Disable TMR1
//    T2CON=0x00;             //Disable TMR2 (ps: for PIC16F690)
//Initial Interrupt
    INTCON=0x00;            //Disable all of interrupt
    PIE1=0x00;
    PIE2=0x00;
    IOCA=0x00;
    IOCB=0x00;
//Initial I/O
    WPUA=0x00;              //Disable RA0~RA5 pull-up
    WPUB=0x00;              //Disable RB0~RB7 pull-up
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    ANSEL=0x07;             //AN0,AN1,AN2
    ANSELH=0x00;
    TRISA=0b00000000;        //RA0~RA7 as output
    TRISB=0b00000000;        //RB4~RB7 as output
    TRISC=0b00000000;        //RC0~RC7 as output
//Initial Comparator
    CM1CON0=0x00;           //Disable Comparator1
    CM2CON0=0x00;           //Disable Comparator2
    VRCON=0x00;            //Disable CVREF
//Initial ADC
    ADCON0=0b10000001;      //ADC Power Up
    ADCON1=0b01010000;      //TAD=Fosc/16
//Initial EUSART
    RCSTA=0x00;             //Disable EUSART
//Initial SSP (SPI or IIC)
    SSPCON=0x00;            //Disable SPI
    SSPCON,0b00000001;      //SPI Master mode(SCK,SDO,SDI as SPI pins),CKP=0,clock=Fosc/4 (8MHz/16 = 0.5MHz)
    SSPSTAT=0b01000000;     //SMP=0,CKE=1
    SSPCONbits.SSPEN=1;     //Enable SPI pin (SCK,SDO,SDI,SS)
}
void init_LCM(void)
{
    LCM_RST=1;
    NOP();
    LCM_CE=0;
    LCM_DC=0;
    WriteSPI(Function_Set_Extended_Commands);
    WriteSPI(Set_Vop);
    WriteSPI(Temperature_control);
    WriteSPI(Bias_system);
    WriteSPI(Function_Set_Normal_Commands);
    WriteSPI(Display_Control);
    LCM_CE=1;
    LCM_clear();     //Clear NOKIA 5110 Screen
}
void LCM_clear(void)
{
    LCM_CE=0;
    LCM_DC=0;
    WriteSPI(0x80);     //Ser Screen X address = 0
    WriteSPI(0x40);     //Ser Screen Y address = 0
    LCM_DC=1;
    for(char x_counter=0;x_counter<84;x_counter++)
    {
        WriteSPI(0x00); WriteSPI(0x00); WriteSPI(0x00);
        WriteSPI(0x00); WriteSPI(0x00); WriteSPI(0x00);
    }
    LCM_CE=1;
}
void LCM_pattern(unsigned char x,unsigned char y,unsigned char ID)
{
    LCM_CE=0;
    LCM_DC=0;
    WriteSPI(x + 0x80);
    WriteSPI(y + 0x40);
    LCM_DC=1;
    for(unsigned char x_counter=0;x_counter<5;x_counter++)
        WriteSPI(pattern[ID][x_counter]);
    LCM_CE=1;
}
signed char WriteSPI(unsigned char data)
{
    unsigned char TempVar;
    TempVar = SSPBUF;           // Clears BF
    PIR1bits.SSPIF = 0;         // Clear interrupt flag
    SSPCONbits.WCOL = 0;	//Clear any previous write collision
    SSPBUF = data;              // write byte to SSPBUF register
    if ( SSPCON & 0x80 )        // test if write collision occurred
        return ( -1 );          // if WCOL bit is set return negative #
    else
    while( !PIR1bits.SSPIF );  // wait until bus cycle complete
    return ( 0 );          // if WCOL bit is not set return non-negative#
}
void LED(unsigned char LED_pin,unsigned char on_off)
{
    switch (LED_pin)
    {
        case 0 :    LED1=on_off;    break;
        case 1 :    LED2=on_off;    break;
        case 2 :    LED3=on_off;    break;
        case 3 :    LED4=on_off;    break;
    }
}

