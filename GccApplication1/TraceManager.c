/*
 * TraceManager.c
 *
 * Created: 2017/10/28 22:37:52
 *  Author: Administrator
 */ 
 
#include "SensorManager.h"
#include "MotorManager.h"
#include "MovingDistance.h"
#include "TraceManager.h"
#include "TracePatternManager.h"
#include "TurnManager.h"

extern void adjustTurnPosition(void);
extern void LED_on(int i);

/*
 * ���ʃg���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�X�^�[�g�R�}���h����M����B
 *   �I�������F�Z���T�ō��^�[�������o���Ē��p���񂪊�������B
 */
void traceCommon(int *counter, int *maxSpeed) {
	// �Z���T�[�l���擾
	getSensors();
	if (currentTraceAction == TRACE_UNDEFINED) {
		_delay_ms(2);// delayTime�̊Ԋu���󂯂�
		return;
	}

#ifdef LOG_INFO_ON
	if ((*counter % 1) == 0) {
		BaseSpeed = BaseSpeed + 1;
		*counter = 0;
	}
#else
	if ((*counter % 6) == 0) {
		BaseSpeed = BaseSpeed + 2;
		*counter = 0;
	}
#endif /* _MODE_SKIP_ */
	if (BaseSpeed > *maxSpeed) {
		BaseSpeed = *maxSpeed;
	}

	Execute(currentTraceAction);
	_delay_ms(1);// delayTime�̊Ԋu���󂯂�
}

/*
 * ���H�G���A 18 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 17 �̃g���[�X���삩��p���j�B
 *   �I�������F�S�[���G���A�����o���ďI�����삪��������B
 */
void traceBackwardArea_18(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	// ���i
	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;

	// AVR�^�C�}�J�n
	AvrTimerStart();

	// �ړ������̌v�����J�n
	StartMeasuringMovingDistance();

	// �ڕW�̋����܂őO�i
	//currentTraceAction = TRACE_STRAIGHT;
	int32_t targetDistance = 110;	//�ڕW���� = 130cm
	while (targetDistance > GetMovingDistance()) {
		// �ړ��������X�V
		UpdateMovingDistance();

		// ���ʃg���[�X����
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// �ړ������̌v�����~
	StopMeasuringMovingDistance();
	_delay_ms(10);

	// AVR�^�C�}��~
	AvrTimerEnd();
	AvrTimerReset();

	// ��~���s
	StopMove();
}

/*
 * ���E�傫�ڂɃ��{�b�g��h�炵���W�O�U�O�ȃ��C���g���[�X�����s
 */
void TreasureFindingLineTrace(int isFirst) {
	int sensorPattern = BIT_000000;
	BaseSpeed = 50;

	sensorPattern = getSensorPattern();

	// ���񓮍�̏ꍇ
	if (isFirst == 0) {
		if (sensorPattern == BIT_100000 ||
		    sensorPattern == BIT_010000 ||
		    sensorPattern == BIT_110000 ||
		    sensorPattern == BIT_001000 ||
		    sensorPattern == BIT_101000 ||
		    sensorPattern == BIT_011000 ||
		    sensorPattern == BIT_111000)
        {
    	    isSearchingLeftSide = 1;
    	    Execute(TRACE_L_TRESURE_FIND);
    	} else {
    	    isSearchingLeftSide = 0;
    	    Execute(TRACE_R_TRESURE_FIND);
		}
		_delay_ms(10);
		return;
	}

	if ((isSearchingLeftSide == 0) &&
	    (sensorPattern == BIT_010000 ||
	    sensorPattern == BIT_001000 ||
	    sensorPattern == BIT_011000 ||
	    sensorPattern == BIT_011100
	    )) {
		// ���C���̉E���T�[�`���ɍ����C�������o������A
		// ���C���̍����T�[�`�ɐ؂�ւ���
		isSearchingLeftSide = 1;
		Execute(TRACE_L_TRESURE_FIND);
	} else if (
	    (isSearchingLeftSide > 0) &&
	    (sensorPattern == BIT_000010 ||
	    sensorPattern == BIT_000100 ||
	    sensorPattern == BIT_000110 ||
	    sensorPattern == BIT_001110
	    )) {
		// ���C���̍����T�[�`���ɉE���C�������o������A
		// ���C���̉E���T�[�`�ɐ؂�ւ���
		isSearchingLeftSide = 0;
		Execute(TRACE_R_TRESURE_FIND);
	}
	
	_delay_ms(10);
}

