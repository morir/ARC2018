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
#define H_MOV_SHOULDER_MOTOR    18	    // ���������ɓ������֐߂̃��[�^�[


// AX-12A Control Table Address
#define CTRL_TBL_ADDR_PRESENT_POSITION_L	(36)	// Lowest byte of Current Position
#define CTRL_TBL_ADDR_PRESENT_POSITION_H	(37)	// Highest byte of Current Position
#define CTRL_TBL_ADDR_PRESENT_LOAD_L        (40)    // ���ݕ��׉��ʃr�b�g
#define CTRL_TBL_ADDR_PRESENT_LOAD_H        (41)    // ���ݕ��׏�ʃr�b�g


#define CorrectionValue		    (20) // �␳�l
#define JointMoveBaseSpeed		(40) // 

// ------------------ Method Definition ------------------
void initArmMotor(void);


/************************************************************************/
// ���ɐݒu���ꂽ�^�[�Q�b�g�����p�`��
// ���������ꂷ��ɕό`����B
/************************************************************************/
void FindFormationOnFloor(void);

/************************************************************************/
// ��̏�ɐݒu���ꂽ�^�[�Q�b�g�����p�`��
// ���������ꂷ��ɕό`����B
/************************************************************************/
void FindFormationOnTable(void);

/************************************************************************/
// �^�[�Q�b�g�^���p�`��
// �^�[�Q�b�g��������4cm���x�����グ����Ԃɕό`����B
/************************************************************************/
void TransportFormation(void);

/************************************************************************/
// ������
// ���̊֐߂͓������Ȃ�
/************************************************************************/
void GrabWithHand(void);

/************************************************************************/
// ����J��
// ���̊֐߂͓������Ȃ�
/************************************************************************/
void OpenHand(void);

/************************************************************************/
// ���o�[��������p�̌`��
// ��������グ��
/************************************************************************/
void DownLeverFormation(void);

/************************************************************************/
// ���n�G���A�ŏ�ɂԂ牺�����Ă���^�[�Q�b�g����p�̌`��
// ��������グ��
/************************************************************************/
void UpperTargetFormation(void);

/************************************************************************/
// ���s�p�̌`��
// �����グ�ăJ������O���Ɍ�����
/************************************************************************/
void RunningFormation(void);


void HandUP(void);
void HandDown(void);

void WristUP(void);
void WristDown(void);

void ElbowUP(void);
void ElbowDown(void);

void ShoulderLeft(void);
void ShoulderRight(void);

void CatchAndReleaseFormation(void);

/************************************************************************/
// ���݂̃��[�^�p�x��\��(Debug�p)
// ���݂̃��[�^�p�x��\������B
/************************************************************************/
void Debug_AllMotorCurrentAngle(void);

/**
 * �ݒ�p�x���ڕW�p�x(���X�e�b�v�֐i��ŗǂ��p�x) �ɂȂ�܂œ��삷�� 
 * @param motorId       ���[�^ID
 * @param speed         �ݒ葬�x
 * @param angle         �ݒ�p�x
 * @param allowRange    ���e�p�x
 *      ���X�e�b�v�֐i�ލۂ̋��e�͈́B
 *      ���̒l��0�ɐݒ肷��ƃ��[�^�̊p�x���ݒ�l�ɒB����܂Ŕ����Ȃ��B
 *      ���̒l��傫������ƁA���[�^�̊p�x���ݒ�l�ɒB���Ȃ��Ă������𔲂���悤�ɂȂ�B
 */
void executeRotate(int motorId, int speed, int angle, int allowRange);

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
int GetCurrentAngle(int motorId);

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
int GetCurrentLoad(int motorId);

#endif /* ARMACTIONMANAGER_H_ */