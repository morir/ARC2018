/*
 * ArmActionManager.h
 *
 * Created: 2017/10/28 22:42:34
 *  Author: Administrator
 */ 


#ifndef ARMACTIONMANAGER_H_
#define ARMACTIONMANAGER_H_

#include <util/delay.h>
#include "include/dynamixel.h"

// ------------------ Defined ------------------
#define HAND_MOTOR              23      // ���֐߂̃��[�^�[
#define WRIST_MOTOR             14      // ���֐߂̃��[�^�[
#define ELBOW_MOTOR             25      // �I�֐߂̃��[�^�[
#define V_MOV_SHOULDER_MOTOR    12      // ���������ɓ������֐߂̃��[�^�[
#define H_MOV_SHOULDER_MOTOR    18	    // ���������ɓ������֐߂̃��[�^�[


// MX-12W Control Table Address
#define CTRL_TBL_ADDR_PRESENT_POSITION_L	(36)	// Lowest byte of Current Position
#define CTRL_TBL_ADDR_PRESENT_POSITION_H	(37)	// Highest byte of Current Position


#define CorrectionValue		(20) // �␳�l

// ------------------ Method Definition ------------------
void initArmMotor(void);
void FindFormation(void);
void CatchAndReleaseFormation(void);
void ArmOpenFormation(void);

void Debug_AllMotorCurrentAngle(void);
void executeRotate(int motorId, int speed, int angle, int targetangle);
int GetCurrentAngle(int motorId);

#endif /* ARMACTIONMANAGER_H_ */