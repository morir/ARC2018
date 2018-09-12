/*
 * TracePatternManager.h
 *
 * Created: 2017/10/28 23:23:48
 *  Author: Administrator
 */ 


#ifndef TRACEPATTERNMANAGER_H_
#define TRACEPATTERNMANAGER_H_

#include "AvrTimer.h"

// ------------------ Defined ------------------

#define HISTORY_MAXSIZE (3)//�����Ǘ��ő吔


// ------------------ Global variables ------------------

// IR Sensor
unsigned int IR[6 + 1];//�v�f���� (�Z���T�� + 1)

int ActionTable[64];

// IR�̏��(BIT�p�^�[��)
int IR_BitPattern;
int IR_BitPatternHistory[HISTORY_MAXSIZE];

int currentCount;

// ------------------ Enum Definition ------------------

enum patternIndex {
	L_TURN,
	L_ROUND_TIGHT,
	L_ROUND_MIDDLE,
	L_ROUND_SOFT,
	STRAIGHT,
	R_ROUND_SOFT,
	R_ROUND_MIDDLE,
	R_ROUND_TIGHT,
	R_TURN,
	UNDEFINED
};

// ------------------ Method Definition ------------------

void initActionTable(void);
void initSensorHistory(void);
void getSensors(void);
int getSensorPattern(void);
int getActionWithHistory(void);
void setSensorHistory(int actionPattern);

#endif /* TRACEPATTERNMANAGER_H_ */