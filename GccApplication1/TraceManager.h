/*
 * TraceManager.h
 *
 * Created: 2017/10/28 22:55:59
 *  Author: Administrator
 */ 


#ifndef TRACEMANAGER_H_
#define TRACEMANAGER_H_


// ------------------ Defined ------------------
#define INPUT_KEY_UP            91
#define INPUT_KEY_DOWN          92
#define INPUT_KEY_LEFT          93
#define INPUT_KEY_RIGHT         94
#define INPUT_KEY_NONE          0
#define INPUT_KEY_ACTION_01     1
#define INPUT_KEY_ACTION_02     2
#define INPUT_KEY_ACTION_03     3
#define INPUT_KEY_ACTION_04     4
#define INPUT_KEY_ACTION_05     5
#define INPUT_KEY_ACTION_06     6
#define INPUT_KEY_ACTION_07     7
#define INPUT_KEY_ACTION_08     8
#define INPUT_KEY_ACTION_09     9
#define INPUT_KEY_ACTION_10     10
#define INPUT_KEY_ACTION_11     11
#define INPUT_KEY_ACTION_12     12
#define INPUT_KEY_ACTION_13     13
#define INPUT_KEY_ACTION_14     14
#define INPUT_KEY_ACTION_15     15
#define INPUT_KEY_ACTION_16     16
#define INPUT_KEY_ACTION_17     17
#define INPUT_KEY_ACTION_18     18
#define INPUT_KEY_ACTION_19     19

// ------------------ Global variables ------------------

// ç°âÒÇÃÉgÉåÅ[ÉXìÆçÏ
int currentTraceAction;

int isSearchingLeftSide;

// ------------------ Method Definition ------------------
void traceCommon(int *counter, int *maxSpeed);

void TreasureFindingLineTrace(int isFirst);

void shortTraceToLeftTurn(void);
void shortTraceToRightTurn(void);

void traceBackLowMoveArea_01(void);

#endif /* TRACEMANAGER_H_ */