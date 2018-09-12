/**
 * @file MovingDistance.c
 * @brief �ړ�����
 * @author f.aimano
 * @date 2017/10/28
 */

#include "AvrTimer.h"
#include "DebugLog.h"
#include "MotorManager.h"
#include "MovingDistance.h"

#define MOVING_DISTANCE_K (0.4)		// movingDistance���v�Z����Ƃ��̌W��

static int32_t movingDistance = 0;	// �ړ�����
static int velocity_0 = 0;			// �����x
static uint32_t lastTime = 0;		// �O��̎���(�~���b)
static MEASUREMENT_STATUS measurementStatus = NOT_MEASURING;	// �ړ������̌v�������

/**
 * �ړ������̌v�����J�n
 * @brief �ړ������̌v�����J�n
 */
void StartMeasuringMovingDistance() {
	measurementStatus = MEASURING;
	movingDistance = 0;
}

/**
 * �ړ������̌v�����~
 * @brief �ړ������̌v�����~
 */
void StopMeasuringMovingDistance() {
	measurementStatus = NOT_MEASURING;
}

/**
 * �ړ��������擾
 * @brief �ړ��������擾
 * @return �ړ�����
 */
int32_t GetMovingDistance() {
	return movingDistance;
}

/**
 * �ړ��������X�V
 * @brief �ړ��������X�V
 */
void UpdateMovingDistance() {
	if(measurementStatus == NOT_MEASURING) {
		// ���v�����̏ꍇ�A�ړ������̍X�V���s��Ȃ��B
		return;
	}
	
	// ���݂̕����t�̑��x(�E���[�^)�擾
	int signedSpeedR = GetCurrentSignedSpeedR();

	// ���݂̕����t�̑��x(�����[�^)�擾
	int signedSpeedL = GetCurrentSignedSpeedL();

	// ���݂̑��x���v�Z
	int velocity = (signedSpeedR + signedSpeedL) / 2;
	
	// �o�ߎ���(msec)���v�Z
	uint32_t currentTime = AvrTimerGet();
	uint32_t elapsedTime = currentTime - lastTime;
	
	// �����x���v�Z
	int acceleration = 0;
	if(0 != elapsedTime) {
		acceleration = (velocity - velocity_0) / elapsedTime;
	}
	
	// ���݂̈ړ��������v�Z
	int32_t currentMovingDistance = velocity_0 * (int32_t)elapsedTime + acceleration *(int32_t)(elapsedTime * elapsedTime) / 2;
	
	// �u�����^�~���b�v����u�����^�b�v�ɕϊ����A�ړ������ɔ��f
	movingDistance = movingDistance + (currentMovingDistance / 1000 * MOVING_DISTANCE_K);
	
	// �����x����ёO��̎��Ԃ��X�V
	velocity_0 = velocity;
	lastTime = currentTime;
}