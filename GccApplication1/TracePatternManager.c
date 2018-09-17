/*
 * TracePatternManager.c
 *
 * Created: 2017/10/28 22:38:20
 *  Author: Administrator
 */ 

#include <string.h>
#include "TracePatternManager.h"
#include "SensorManager.h"
#include "MotorManager.h"
#include "DebugLog.h"

/**
* �Z���T�[�l��Bit�p�^�[�����擾����B
* @brief �Z���T�[�l���Q�Ƃ��A�Ή�����A�N�V�������擾����B
* @return �߂�l�̐���
*/
int getSensorPattern(void) {
	// LED��ݒ�
	//setLED();
	
	// �Z���T�[�l���擾
	getSensors();
	return IR_BitPattern;
}

/**
* Bit�p�^�[���̗���������������B
* @brief Bit�p�^�[���̗����𒼐i��Bit�p�^�[���ŏ���������B
* @return �߂�l�̐���
*/
void initSensorHistory(void) {
	memset(IR, 0, sizeof(IR));
	IR_BitPattern = BIT_000000;
	currentCount = 0;
	memset(IR_BitPatternHistory, IR_BitPattern, sizeof(IR_BitPatternHistory));
}

/**
 * �Z���T�[�l���擾
 * @brief �Z���T�[�l���擾
 * @return �Ȃ�
 * @detail �Z���T�[�l���擾���AIR[]�����IR_BitPattern���X�V����B
 */
void getSensors(void) {
	/* ���݂̃J�E���^�l���X�V */
    currentCount = ((currentCount + 1) % HISTORY_MAXSIZE);
	/* �Z���T�[�l���擾 */
    ReadIRSensors(IR);
	
	/* IR��Ԃ�BIT�p�^�[���ɕϊ� */
	IR_BitPattern = 0;
	if (IR[RIGHT_OUTSIDE] <= COMPARE_VALUE_RIGHTSIDE)	IR_BitPattern |= BIT_RIGHT_OUTSIDE_ON;
	if (IR[RIGHT_CENTER]  <= COMPARE_VALUE)	IR_BitPattern |= BIT_RIGHT_CENTER_ON;
	if (IR[RIGHT_INSIDE]  <= COMPARE_VALUE)	IR_BitPattern |= BIT_RIGHT_INSIDE_ON;
	if (IR[LEFT_INSIDE]   <= COMPARE_VALUE)	IR_BitPattern |= BIT_LEFT_INSIDE_ON;
	if (IR[LEFT_CENTER]   <= COMPARE_VALUE)	IR_BitPattern |= BIT_LEFT_CENTER_ON;
	if (IR[LEFT_OUTSIDE]  <= COMPARE_VALUE_LEFTSIDE)	IR_BitPattern |= BIT_LEFT_OUTSIDE_ON;

	IR_BitPatternHistory[currentCount] = IR_BitPattern;
	
    LOG_INFO("sensor %3d: %3d: %3d: %3d: %3d: %3d \r\n",
			 IR[LEFT_OUTSIDE], IR[LEFT_CENTER], IR[LEFT_INSIDE],
			 IR[RIGHT_INSIDE], IR[RIGHT_CENTER], IR[RIGHT_OUTSIDE]);
    LOG_DEBUG("IR[L %1d%1d%1d%1d%1d%1d R]\r\n",
			  ((IR[LEFT_OUTSIDE]  <= COMPARE_VALUE_RIGHTSIDE) ? 1 : 0),
			  ((IR[LEFT_CENTER]   <= COMPARE_VALUE) ? 1 : 0),
			  ((IR[LEFT_INSIDE]   <= COMPARE_VALUE) ? 1 : 0),
			  ((IR[RIGHT_INSIDE]  <= COMPARE_VALUE) ? 1 : 0),
			  ((IR[RIGHT_CENTER]  <= COMPARE_VALUE) ? 1 : 0),
			  ((IR[RIGHT_OUTSIDE] <= COMPARE_VALUE_LEFTSIDE) ? 1 : 0));
}

