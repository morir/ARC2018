/*
 * TurnManager.h
 *
 * Created: 2017/10/28 22:55:59
 *  Author: Administrator
 */ 


#ifndef TURNMANAGER_H_
#define TURNMANAGER_H_


// ------------------ Defined ------------------

#define SLOW_TURN_RATE_BY_BASE	(50)//�x�[�X��20%�̑���
#define STOP_JUDGE_MAX_LIMIT	(10)//��~����̏���l

// ------------------ Global variables ------------------


// ------------------ Method Definition ------------------

int initLeftTurnAction(int maxVal);
int initRightTurnAction(int maxVal);

int executeLeftTurn(void);
int executeRightTurn(void);

void executeLeftTurnFromOnLine(void);
void executeRightTurnFromOnLine(void);
void adjustTurnPosition(void);

#endif /* TURNMANAGER_H_ */