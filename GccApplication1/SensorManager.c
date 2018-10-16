/*
 * SensorManager.c
 *
 * Created: 2014/08/19 18:56:34
 *  Author: Administrator
 */ 

#include <string.h>
#include <util/delay.h>
#include "SensorManager.h"
#include "DebugLog.h"

#define IR_SIZE ADC_PORT_6 + 1

volatile unsigned char count_1ms = 0;
volatile unsigned char count_10ms = 0;
volatile unsigned char count_50ms = 0;
volatile unsigned char count_100ms = 0;
//int sensorValue[6] = {0};

void initIRSensor(void) {

 	memset(IRArrays, 0, sizeof(IRArrays));
   
    //DDRA  = 0xFF;   // PORTA as output
    //PORTA = 0x00;   // Enable the pull-up on PORTA7
    //
    //DDRF  = 0x00;   // PORTF as input
    //PORTF = 0xff;   // Enable the pull-up on PORTF all
    //
    //ADMUX = ADC_PORT_1;     // ADC Port 1 Select
    //ADCSRA |= (1 << ADLAR);
    //ADCSRA |= (1 << ADPS2) | (1 << ADPS1);  // Clock 1/64div.
    //ADCSRA |= (1 << ADEN);  // ADC Enable

	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC Enable, Clock 1/128div.
	ADMUX = ADC_PORT_1; // ADC Port X Select
    
}

unsigned int ReadIRSensor(unsigned int ch) {
    ADMUX = ch;

    //Start Single conversion
    ADCSRA |= (1 << ADIF);
    ADCSRA |= (1 << ADSC);
    
    //Wait or conversion to complete
    while( ! (ADCSRA & (1<<ADIF))) ;
    
    //Clear ADIF by writing one to it, the loop ends when ADIF is set to 1.
    //The conversion is now complete
    
    return(ADC);
    
}

void ReadIRSensors(unsigned int * sensors) {
    unsigned int i = 0;
    for (i = ADC_PORT_1; i <= ADC_PORT_6; i++) {
        sensors[i] = ReadIRSensor(i);
    }
    return;
}

int updateIrSensor(int type) {
    switch (type) {
        case 0:
        ADMUX = ADC_PORT_1;
        PORTA &= ~0x80;
        break;
        case 1:
        ADMUX = ADC_PORT_2;
        PORTA &= ~0x40;
        break;
        case 2:
        ADMUX = ADC_PORT_3;
        PORTA &= ~0x20;
        break;
        case 3:
        ADMUX = ADC_PORT_4;
        PORTA &= ~0x10;
        break;
        case 4:
        ADMUX = ADC_PORT_5;
        PORTA &= ~0x08;
        break;
        case 5:
        ADMUX = ADC_PORT_6;
        PORTA &= ~0x04;
        break;
    }
    
    _delay_us(12);
    ADCSRA |= (1 << ADIF); // AD-Conversion Interrupt Flag Clear
    ADCSRA |= (1 << ADSC); // AD-Conversion Start
    while( !(ADCSRA & (1 << ADIF)) ); // Wait until AD-Conversion complete
    PORTA = 0xFC;				// IR-LED Off
    
    return (ADC);
}

void getIrSensor(void) {
	IRArrays[ADC_PORT_1] = updateIrSensor(0);
	IRArrays[ADC_PORT_2] = updateIrSensor(1);
	IRArrays[ADC_PORT_3] = updateIrSensor(2);
	IRArrays[ADC_PORT_4] = updateIrSensor(3);
	IRArrays[ADC_PORT_5] = updateIrSensor(4);
	IRArrays[ADC_PORT_6] = updateIrSensor(5);
}

void timer_init(void) {
    //TCCR1B = 0x00;  // stop
    //TCNT1 = 0x00;   // set count
    //OCR1A = 1;   // 1us * 1024 -> 1.024ms
    //TCCR1A = (1 << WGM01);  // CTC mode
    //TIMSK1 |= (1 << OCIE1A);
    //TCCR1B = (1 << CS12) | (1 << CS10);  // start timer Clock/1024

	// Timer0. 1 count = 1us. Max = 256 * 1us = 256ms
	TCCR0A = (1<<WGM01);			// CTC mode
	TCCR0B |= (1<<CS01)|(1<<CS00);	// Prescaler = FCPU/64
	TIMSK0 = (1<<OCIE0A);			// コンペアマッチAの割り込みを設定
	OCR0A = 250;					// 1msでコンペアマッチ
}

ISR(TIMER1_COMPA_vect) {
    // Update Sensors
    //unsigned int * IR = NULL;
    //
    //ReadIRSensors(IRArrays);
    //LOG_DEBUG( "LEFT_OUTSIDE  :%d\r\n", IR[LEFT_OUTSIDE]);
    //LOG_DEBUG( "LEFT_CENTER   :%d\r\n", IR[LEFT_CENTER]);
    //LOG_DEBUG( "LEFT_INSIDE   :%d\r\n", IR[LEFT_INSIDE]);
    //LOG_DEBUG( "RIGHT_INSIDE  :%d\r\n", IR[RIGHT_INSIDE]);
    //LOG_DEBUG( "RIGHT_CENTER  :%d\r\n", IR[RIGHT_CENTER]);
    //LOG_DEBUG( "RIGHT_OUTSIDE :%d\r\n", IR[RIGHT_OUTSIDE]);

	count_1ms++;
	// 10ms
	if (count_1ms == 10) {
    	count_1ms = 0;
    	count_10ms++;
    	count_50ms++;
	}

	// 50ms
	if (count_50ms == 5) {
    	count_50ms = 0;
    	getIrSensor();		// IR update
    	//		if (!LOG_DISABLE) printf("sensorA = %d\n", sensorValue[0]);
    	//		if (!LOG_DISABLE) printf("sensorB = %d\n\n", sensorValue[1]);
	}
}
