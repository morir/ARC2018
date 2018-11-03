/*
 * IncFile1.h
 *
 * Created: 2014/07/03 14:01:02
 *  Author: sapporo62
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "include/serial.h"
#include "TraceManager.h"

#define SERIAL_BUFFER_SIZE      32
#define SERIAL_DATA_NOTUPDATE   0
#define SERIAL_DATA_UPDATED     1
#define DATA_UPDATED_MAX_COUNT  1000

extern void initSerial(void);
extern void clearSerialBuffer();
extern int checkSerialRead(void);
extern char * getReadBuffer();

// ------------------ Method Definition ------------------
void getInputKey(int *outInputKey);



#endif /* INCFILE1_H_ */