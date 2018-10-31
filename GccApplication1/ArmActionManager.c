/*
 * ArmActionManager.c
 *
 * Created: 2017/10/28 22:38:53
 *  Author: Administrator
 */ 

#include "ArmActionManager.h"

#include "MotorManager.h"
#include "AvrTimer.h"
#include "DebugLog.h"


/************************************************************************/
// Arm�p���[�^�̏����ݒ�
// Arm�p���[�^��󕨌����p�`��(���^�[�Q�b�g����p)�̈ʒu�ɐݒ�
/************************************************************************/
void initArmMotor(void) 
{
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
	executeRotate(ELBOW_MOTOR, 50, 350, 10);
	executeRotate(WRIST_MOTOR, 50, 320, 10);
	executeRotate(HAND_MOTOR, 50, 780, 10);
}

/************************************************************************/
// ���ɐݒu���ꂽ�^�[�Q�b�g�����p�`��
// ���������ꂷ��ɕό`����B
/************************************************************************/
void FindFormationOnFloor(void)
{
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
	executeRotate(ELBOW_MOTOR, 50, 350, 10);
	executeRotate(WRIST_MOTOR, 50, 320, 10);
	executeRotate(HAND_MOTOR, 50, 780, 10);
}

/************************************************************************/
// ��̏�ɐݒu���ꂽ�^�[�Q�b�g�����p�`��
// ���������ꂷ��ɕό`����B
/************************************************************************/
void FindFormationOnTable(void)
{
    executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
    executeRotate(ELBOW_MOTOR, 50, 460, 10);
    executeRotate(WRIST_MOTOR, 50, 430, 10);
    executeRotate(HAND_MOTOR, 50, 780, 10);
}

/************************************************************************/
// �^�[�Q�b�g�^���p�`��
// �^�[�Q�b�g��������4cm���x�����グ����Ԃɕό`����B
/************************************************************************/
void TransportFormation(void)
{
    executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
    executeRotate(ELBOW_MOTOR, 50, 490, 10);
    executeRotate(WRIST_MOTOR, 50, 535, 10);
}

/************************************************************************/
// ������
// ���̊֐߂͓������Ȃ�
/************************************************************************/
void GrabWithHand(void)
{
	// ������
	executeRotate(HAND_MOTOR, 50, 570, 1000);
}

/************************************************************************/
// ����J��
// ���̊֐߂͓������Ȃ�
/************************************************************************/
void OpenHand(void)
{
    // ����J��
    executeRotate(HAND_MOTOR, 50, 780, 1000);
}

/************************************************************************/
// �󕨉�������ڗp�`��
// �󕨂�������A���ڂ���
// �i�K�I�ɓ��삳���󕨂𗎂Ƃ�
/************************************************************************/
void CatchAndReleaseFormation(void)
{
	//-- �͂�
	executeRotate(HAND_MOTOR, 200, 512, 512 );

	//-- �����グ�J�n	
	executeRotate(ELBOW_MOTOR, 100, 250, 250);
	MotorControlJoint(ELBOW_MOTOR, 100, 680);

	//-- �����グ�r��
	executeRotate(ELBOW_MOTOR, 100, 500, 500);

	//-- ���Ƃ����O
	executeRotate(ELBOW_MOTOR, 100, 700, 700);
	MotorControlJoint( ELBOW_MOTOR, 100, 700 );
	_delay_ms(500);//�K�؂ȃE�F�C�g���Ԃ�ݒ�

	//-- ���Ƃ�
	executeRotate( WRIST_MOTOR, 200, 620, 620 );
	
	_delay_ms(700);//1�b�҂˓���ɍ��킹�ĕύX���Ă�������

	//-- �󕨌����p�`�ԂɈڍs���邽�߂̏���
	MotorControlJoint(ELBOW_MOTOR, 100, 280);
	MotorControlJoint(WRIST_MOTOR, 200, 512);
	MotorControlJoint(ELBOW_MOTOR, 100, 400);	
	executeRotate(ELBOW_MOTOR, 100, 120, 120);
	
	// �󕨌����p���C���g���[�X�`�Ԃɖ߂�
	FindFormationOnFloor();
}


/************************************************************************/
// ���݂̃��[�^�p�x��\��(Debug�p)
// ���݂̃��[�^�p�x��\������B
/************************************************************************/
void Debug_AllMotorCurrentAngle(void)
{
	LOG_ERROR("GetCurrentAngle(H_MOV_SHOULDER_MOTOR) %d\r\n", GetCurrentAngle(H_MOV_SHOULDER_MOTOR));
	LOG_ERROR("GetCurrentAngle(ELBOW_MOTOR) %d\r\n", GetCurrentAngle(ELBOW_MOTOR));
	LOG_ERROR("GetCurrentAngle(WRIST_MOTOR) %d\r\n", GetCurrentAngle(WRIST_MOTOR));
	LOG_ERROR("GetCurrentAngle(HAND_MOTOR) %d\r\n", GetCurrentAngle(HAND_MOTOR));
}

/**
 * �ݒ�p�x���ڕW�p�x(���X�e�b�v�֐i��ŗǂ��p�x) �ɂȂ�܂œ��삷�� 
 * @param motorId       ���[�^ID
 * @param speed         �ݒ葬�x
 * @param angle         �ݒ�p�x
 * @param allowRange    ���e�p�x(���X�e�b�v�֐i��ŗǂ��p�x) 
 */
void executeRotate(int motorId, int speed, int angle, int allowRange){
	//�ݒ�p�x�ւ̓�������s
	MotorControlJoint( motorId, speed, angle );

	if (allowRange >= 1000) {
        // allowRange��1000���傫���ꍇ�͂����ɏ����𔲂���B
        _delay_ms(10);
        return;
    }

    int currentAngle = GetCurrentAngle(motorId);// ���݂̊p�x���X�V
    
	if((angle - currentAngle) > 0) 
	{
        // ���݊p�x�����ݒ�p�x���傫���ꍇ
		// �ڕW�p�x�ɒB���Ă��Ȃ��Ԃ͓��삷��
		while( (angle - allowRange) >= currentAngle)
		{
			_delay_ms(10);//�K�؂ȃE�F�C�g���Ԃ�ݒ�
            currentAngle = GetCurrentAngle(motorId);// ���݂̊p�x���X�V
		}
	}
	else
	{
        // ���݊p�x�����ݒ�p�x���������ꍇ
		// �ڕW�p�x�ɒB���Ă��Ȃ��Ԃ͓��삷��
		while( currentAngle >= (angle + allowRange))
		{
			_delay_ms(10);//�K�؂ȃE�F�C�g���Ԃ�ݒ�
            currentAngle = GetCurrentAngle(motorId);// ���݂̊p�x���X�V
		}		
	}
}

/**
 * ���݂̃��[�^�p�x�擾
 * @brief  ���݂̃��[�^�p�x�擾
 * @param  motorId ���[�^ID
 * @return ���݂̊p�x
 * @detail ��ʃo�C�g2bit�A����8bit���猻�݂̊p�x���擾����B
 *         �p�P�b�g�ʐM���s���A�O��̑��x��Ԃ��B
 *         �o�͎��F0�`300���A0�`1023�@�������F150�� = 512
 *         300�`360���̊ԁF�s��l
 *
 *         ���L�̃��[�^ID����̓p�����[�^�Ƃ��邱�ƁB
 *         H_MOV_SHOULDER_MOTOR 18      // Shoulder Motor address(�����[�^)
 *         ELBOW_MOTOR          25      // Elbow arm Motor address(�I���[�^)
 *         WRIST_MOTOR          14      // Wrist Motor address(��񃂁[�^)
 *         HAND_MOTOR           23      // Hand Motor address(�胂�[�^)
 */
int GetCurrentAngle(int motorId) {
	int readValueHigh = 0;	// ��ʃo�C�g
	int readValueLow = 0;	// ���ʃo�C�g
	static int angle = 0;	// ���݂̈ʒu
	
	// ��ʃo�C�g�擾
	readValueHigh = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_POSITION_H) & 0x03;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// �p�P�b�g�ʐM���s���A�O��l��Ԃ��B
		return angle;
	}
	// ���ʃo�C�g�擾
	readValueLow  = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_POSITION_L) & 0xFF;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// �p�P�b�g�ʐM���s���A�O��l��Ԃ��B
		return angle;
	}
	// ��ʃo�C�g�Ɖ��ʃo�C�g���猻�݂̈ʒu���v�Z
	angle = ((readValueHigh << 8) + readValueLow);
	LOG_DEBUG("GetCurrentAngle(%d) is %d\n", motorId, angle);

	return angle;
}

/**
 * ���݂̃��[�^���׎擾
 * @brief  ���݂̃��[�^���׎擾
 * @param  motorId ���[�^ID
 * @return ���݂̕���
 * @detail ��ʃo�C�g3bit�A����8bit���猻�݂̕��ׂ��擾����B
 *         �o�́F0�`1023 1023�Ȃ�100%�̕��׏��
 *          ��ʃo�C�g��4bit�ڂ��擾���邱�Ƃŕ��ו������擾�ł��邪�{�֐��ł͖��g�p�Ƃ���B
 *
 *         ���L�̃��[�^ID����̓p�����[�^�Ƃ��邱�ƁB
 *         H_MOV_SHOULDER_MOTOR 18      // Shoulder Motor address(�����[�^)
 *         ELBOW_MOTOR          25      // Elbow arm Motor address(�I���[�^)
 *         WRIST_MOTOR          14      // Wrist Motor address(��񃂁[�^)
 *         HAND_MOTOR           23      // Hand Motor address(�胂�[�^)
 */
int GetCurrentLoad(int motorId) {
	int readValueHigh = 0;	// ��ʃo�C�g
	int readValueLow = 0;	// ���ʃo�C�g
	static int loadVal = 0;	// ���݂̕���
	
	// ��ʃo�C�g�擾
	readValueHigh = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_LOAD_H) & 0x02;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// �p�P�b�g�ʐM���s���A�O��l��Ԃ��B
		return loadVal;
	}
	// ���ʃo�C�g�擾
	readValueLow  = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_LOAD_L) & 0xFF;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// �p�P�b�g�ʐM���s���A�O��l��Ԃ��B
		return loadVal;
	}
	// ��ʃo�C�g�Ɖ��ʃo�C�g���猻�݂̕��ׂ��v�Z
	loadVal = ((readValueHigh << 8) + readValueLow);
	LOG_DEBUG("GetCurrentAngle(%d) is %d\n", motorId, angle);

	return loadVal;
}
