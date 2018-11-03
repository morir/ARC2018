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
	executeRotate(WRIST_MOTOR, 180, 260, 5);
	executeRotate(ELBOW_MOTOR, 100, 350, 10);
	executeRotate(WRIST_MOTOR, 80, 320, 5);
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 1000);
	executeRotate(HAND_MOTOR, 300, 780, 1000);
}

/************************************************************************/
// ���ɐݒu���ꂽ�^�[�Q�b�g�����p�`��
// ���������ꂷ��ɕό`����B
/************************************************************************/
void FindFormationOnFloor(void)
{
	executeRotate(WRIST_MOTOR, 180, 260, 5);
	executeRotate(ELBOW_MOTOR, 100, 350, 10);
	executeRotate(WRIST_MOTOR, 80, 320, 5);
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 1000);
	executeRotate(HAND_MOTOR, 300, 780, 1000);
}

/************************************************************************/
// ��̏�ɐݒu���ꂽ�^�[�Q�b�g�����p�`��
// ���������ꂷ��ɕό`����B
/************************************************************************/
void FindFormationOnTable(void)
{
	executeRotate(WRIST_MOTOR, 180, 260, 5);
    executeRotate(ELBOW_MOTOR, 50, 460, 10);
    executeRotate(WRIST_MOTOR, 50, 430, 10);
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 1000);
	executeRotate(HAND_MOTOR, 400, 780, 1000);
}

/************************************************************************/
// �^�[�Q�b�g�^���p�`��
// �^�[�Q�b�g��������4cm���x�����グ����Ԃɕό`����B
/************************************************************************/
void TransportFormation(void)
{
    executeRotate(WRIST_MOTOR, 120, 300, 10);
    executeRotate(ELBOW_MOTOR, 100, 535, 100);
    executeRotate(WRIST_MOTOR, 60, 490, 20);
    executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
}

/************************************************************************/
// ������
// ���̊֐߂͓������Ȃ�
/************************************************************************/
void GrabWithHand(void)
{
	// ������
	executeRotate(HAND_MOTOR, 300, 670, 10);
	executeRotate(HAND_MOTOR, 120, 570, 10);
}

/************************************************************************/
// ����J��
// ���̊֐߂͓������Ȃ�
/************************************************************************/
void OpenHand(void)
{
    // ����J��
    executeRotate(HAND_MOTOR, 40, 600, 10);
    executeRotate(HAND_MOTOR, 120, 650, 10);
    executeRotate(HAND_MOTOR, 250, 780, 1000);
}

/************************************************************************/
// ���o�[��������p�̌`��
// ��������グ��
/************************************************************************/
void DownLeverFormation(void)
{
    executeRotate(WRIST_MOTOR, 120, 300, 10);
    executeRotate(ELBOW_MOTOR, 100, 535, 100);
    executeRotate(WRIST_MOTOR, 60, 490, 20);
    executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
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
    
    LOG_INFO("executeRotate 1 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));

	// �ڕW�p�x�ɒB���Ă��Ȃ��Ԃ͓��삷��
    if (currentAngle < angle)
    {
        // ���݊p�x�����ݒ�p�x���������ꍇ
        // �ڕW�p�x�ɒB���Ă��Ȃ��Ԃ͓��삷��
        while(1)
        {
            if (currentAngle >= (angle - allowRange))
            {
                LOG_INFO("executeRotate 2-1 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
                break;
            }
    	    _delay_ms(5);//�K�؂ȃE�F�C�g���Ԃ�ݒ�
    	    currentAngle = GetCurrentAngle(motorId);// ���݂̊p�x���X�V
            LOG_INFO("executeRotate 2 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
        }
    }
    else
    {
        // ���݊p�x�����ݒ�p�x���傫���ꍇ
        // �ڕW�p�x�ɒB���Ă��Ȃ��Ԃ͓��삷��
        while(1)
        {
            if (currentAngle <= (angle + allowRange))
            {
                LOG_INFO("executeRotate 3-1 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
                break;
            }
    	    _delay_ms(5);//�K�؂ȃE�F�C�g���Ԃ�ݒ�
    	    currentAngle = GetCurrentAngle(motorId);// ���݂̊p�x���X�V
            LOG_INFO("executeRotate 3 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
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
	LOG_INFO("GetCurrentAngle(%d) is %d\n", motorId, angle);

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
