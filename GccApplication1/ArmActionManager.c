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
// Arm�p���[�^��󕨌����p�`��(���C���g���[�X�p)�̈ʒu�ɐݒ�
/************************************************************************/
void initArmMotor(void) {

	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 0);
	executeRotate(V_MOV_SHOULDER_MOTOR, 50, 512, 0);
	executeRotate(ELBOW_MOTOR, 50, 512, 0);
	executeRotate(WRIST_MOTOR, 50, 512, 0);
	executeRotate(HAND_MOTOR, 50, 512, 0);
}

/************************************************************************/
// �^�[�Q�b�g�����p�`��
// �^�[�Q�b�g�����p�̌`��ɕό`����B
/************************************************************************/
void FindFormation(void)
{
	executeRotate(H_MOV_SHOULDER_MOTOR, 60, 512, 0);
	executeRotate(V_MOV_SHOULDER_MOTOR, 60, 590, 590);
	executeRotate(ELBOW_MOTOR, 60, 90, 90);
	executeRotate(WRIST_MOTOR, 60, 380, 380);
	executeRotate(HAND_MOTOR, 60, 800, 800);
}


/************************************************************************/
// �󕨉���`��(�����ĂЂ炢�����)
// �󕨂�������邽�߂̏����`�Ԃɂ���
/************************************************************************/
void ArmOpenFormation(void)
{
	//-- �����ĂЂ炭
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 0);
	executeRotate(HAND_MOTOR, 200, 770, 770);
	executeRotate(ELBOW_MOTOR, 150, 360, 360);
	executeRotate(WRIST_MOTOR, 150, 120, 120);
	executeRotate(V_MOV_SHOULDER_MOTOR, 150, 500, 500);
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
	MotorControlJoint(V_MOV_SHOULDER_MOTOR, 100, 500);
	MotorControlJoint(ELBOW_MOTOR, 100, 680);

	//-- �����グ�r��
	executeRotate(ELBOW_MOTOR, 100, 500, 500);

	//-- ���Ƃ����O
	executeRotate(ELBOW_MOTOR, 100, 700, 700);
	MotorControlJoint( ELBOW_MOTOR, 100, 700 );
	executeRotate( V_MOV_SHOULDER_MOTOR, 100, 410, 410 );
	_delay_ms(500);//�K�؂ȃE�F�C�g���Ԃ�ݒ�

	//-- ���Ƃ�
	executeRotate( WRIST_MOTOR, 200, 620, 620 );
	
	_delay_ms(700);//1�b�҂˓���ɍ��킹�ĕύX���Ă�������

	//-- �󕨌����p�`�ԂɈڍs���邽�߂̏���
	MotorControlJoint(ELBOW_MOTOR, 100, 280);
	executeRotate(V_MOV_SHOULDER_MOTOR, 40, 580, 580);
	MotorControlJoint(WRIST_MOTOR, 200, 512);
	MotorControlJoint(ELBOW_MOTOR, 100, 400);	
	MotorControlJoint(V_MOV_SHOULDER_MOTOR, 100, 630);
	executeRotate(ELBOW_MOTOR, 100, 120, 120);
	
	// �󕨌����p���C���g���[�X�`�Ԃɖ߂�
	FindFormation();
}


/************************************************************************/
// ���݂̃��[�^�p�x��\��(Debug�p)
// ���݂̃��[�^�p�x��\������B
/************************************************************************/
void Debug_AllMotorCurrentAngle(void)
{
	LOG_ERROR("GetCurrentAngle(H_MOV_SHOULDER_MOTOR) %d\r\n", GetCurrentAngle(H_MOV_SHOULDER_MOTOR));
	LOG_ERROR("GetCurrentAngle(V_MOV_SHOULDER_MOTOR) %d\r\n", GetCurrentAngle(V_MOV_SHOULDER_MOTOR));
	LOG_ERROR("GetCurrentAngle(ELBOW_MOTOR) %d\r\n", GetCurrentAngle(ELBOW_MOTOR));
	LOG_ERROR("GetCurrentAngle(WRIST_MOTOR) %d\r\n", GetCurrentAngle(WRIST_MOTOR));
	LOG_ERROR("GetCurrentAngle(HAND_MOTOR) %d\r\n", GetCurrentAngle(HAND_MOTOR));
}

/**
 * �ݒ�p�x���ڕW�p�x(���X�e�b�v�֐i��ŗǂ��p�x) �ɂȂ�܂œ��삷�� 
 * @param motorId     ���[�^ID
 * @param speed       �ݒ葬�x
 * @param angle       �ݒ�p�x
 * @param targetangle �ڕW�p�x(���X�e�b�v�֐i��ŗǂ��p�x) 
 */
void executeRotate(int motorId, int speed, int angle, int targetangle){
	//�ݒ�p�x�ւ̓�������s
	MotorControlJoint( motorId, speed, angle );

	if (angle == 0) {
        // angle��0�̏ꍇ�͂����ɏ����𔲂���B
        _delay_ms(10);
        return;
    }

	if((angle - GetCurrentAngle(motorId)) > 0) 
	{
		// �ڕW�p�x�ɒB���Ă��Ȃ��Ԃ͓��삷��
		while( (targetangle - CorrectionValue) > GetCurrentAngle(motorId))
		{
			_delay_ms(10);//�K�؂ȃE�F�C�g���Ԃ�ݒ�
		}
	}
	else
	{
		// �ڕW�p�x�ɒB���Ă��Ȃ��Ԃ͓��삷��
		while( GetCurrentAngle(motorId) > (targetangle + CorrectionValue))
		{
			_delay_ms(10);//�K�؂ȃE�F�C�g���Ԃ�ݒ�
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
 *         SHOULDER_MOTOR       12      // Shoulder Motor address(�����[�^)
 *         UPPER_ARM_MOTOR      25      // Upper arm Motor address(��r���[�^)
 *         FORE_ARM_MOTOR       14      // ForeArm Motor address(�O�r���[�^)
 *         WRIST_MOTOR          23      // Wrist Motor address(��񃂁[�^)
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
