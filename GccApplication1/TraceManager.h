/*
 * TraceManager.h
 *
 * Created: 2017/10/28 22:55:59
 *  Author: Administrator
 */ 


#ifndef TRACEMANAGER_H_
#define TRACEMANAGER_H_


// ------------------ Defined ------------------


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