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
	//memset(IR, 0, sizeof(IR));
	//IR_BitPattern = BIT_000000;
	//currentCount = 0;
	//memset(IR_BitPatternHistory, IR_BitPattern, sizeof(IR_BitPatternHistory));
}

/**
 * �Z���T�[�l���擾
 * @brief �Z���T�[�l���擾
 * @return �Ȃ�
 * @detail �Z���T�[�l���擾���AIR[]�����IR_BitPattern���X�V����B
 */
void getSensors(void) {

}

