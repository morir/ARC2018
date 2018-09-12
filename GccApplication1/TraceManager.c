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

void initTraceAction() {
	currentTraceAction = TRACE_STRAIGHT;
	isSearchingLeftSide = 0;
}

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
	currentTraceAction = getActionWithHistory();
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
 * ���H�G���A 1 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�X�^�[�g�R�}���h����M����B
 *   �I�������F�Z���T�ō��^�[�������o���Ē��p���񂪊�������B
 */
 void traceForwardArea_01(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	//��������i�����������i�j
	StraightMove();
	_delay_ms(100);	// 10ms �Ԋu���󂯂�

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 2 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 1 �̃g���[�X���삩��p���j�B
 *   �I�������F�Z���T�ō��^�[�������o���Ē��p���񂪊�������B
 */
 void traceForwardArea_02(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 3 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 2 �̃g���[�X���삩��p���j�B
 *   �I�������F�Z���T�ō��^�[�������o���Ē��p���񂪊�������B
 */
 void traceForwardArea_03(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 4 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 3 �̃g���[�X���삩��p���j�B
 *   �I�������F�Z���T�ŉE�^�[�������o���Ē��p���񂪊�������B
 */
 void traceForwardArea_04(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// �E������s
	currentTraceAction = executeRightTurn();
	//setSensorHistory(executeRightTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 5 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 4 �̃g���[�X���삩��p���j�B
 *   �I�������F�Z���T�ŉE�^�[�������o���Ē��p���񂪊�������B
 */
 void traceForwardArea_05(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// �E������s
	currentTraceAction = executeRightTurn();
	//setSensorHistory(executeRightTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 1 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i�܂�Ԃ��_�̃g���[�X���삩��p���j�B
 *   �I�������F�Z���T�ō��^�[�������o���Ē��p���񂪊�������B
 */
 void traceBackwardArea_01(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 2 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 1 �̃g���[�X���삩��p���j�B
 *   �I�������F�Z���T�ō��^�[�������o���Ē��p���񂪊�������B
 */
 void traceBackwardArea_02(void) {
	int counter = 0;
	int maxSpeed = BASE_SPEED_BY_SLOWMOVE;

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 3 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 2 �̃g���[�X���삩��p���j�B
 *   �I�������F�Z���T�ŉE�^�[�������o���Ē��p���񂪊�������B
 */
 void traceBackwardArea_03(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	
	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��~���s
	stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
	LED_on(1);
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 4 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 3 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_04(void) {
    int sensorPattern = BIT_000000;
	int findAnySensorCount = 0;
	int loopCount = 0;
	StraightMove();
	_delay_ms(200);

	// �Z���T�[�̂����ꂩ�������肷��܂ŁA���i�p��
	while (1) {
		StraightMove();
		sensorPattern = getSensorPattern();
		// 3��A�����Ĕ����肵���烋�[�v�𔲂���
		if (sensorPattern != BIT_000000) {
			findAnySensorCount++;
			if (findAnySensorCount > 2) {
				break;
			}
		}
		if (loopCount > 700) {
			break;
		}
		loopCount++;
		_delay_ms(1);
	}

	// ��~���s
	stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);

	// �Z���T�[�l�ɉ����Đ�������s
	// TODO:����

	// ����I����A��~���s
	StopMove();
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
}

/*
 * ���H�G���A 6 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 5 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 //void traceBackwardArea_06(void) {
	//int counter = 0;
	//int maxSpeed = BASE_SPEED_BY_TURF_AREA;
//
	//while (currentTraceAction != TRACE_R_TURN) {
		//traceCommon(&counter, &maxSpeed);
		//// �������Ȃ�
		//maxSpeed = BASE_SPEED_BY_TURF_AREA;
	//}
//
	//// �E������s
	//executeRightTurn();
	//BaseSpeed = BASE_SPEED_BY_TURF_AREA;
//}

/*
 * ���H�G���A 6 �̃g���[�X����i�󕨂Q����̃o�b�N�j
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 5 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
void traceBackwardArea_06(void) {
	 int counter = 0;
	 int maxSpeed = BASE_SPEED_BY_TURF_AREA;

	 while (currentTraceAction != TRACE_R_TURN) {
		//�o�b�N����B
		// ������
	 }

	 //�K�v�ɉ����Ĉʒu�𒲐�

	 // �E������s
	 executeRightTurn();
	 BaseSpeed = BASE_SPEED_BY_TURF_AREA;
}

/*
 * ���H�G���A 7 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 6 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_07(void) {
	int counter = 0;
	int maxSpeed = BASE_SPEED_BY_TURF_AREA;

	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		// �������Ȃ�
		maxSpeed = BASE_SPEED_BY_TURF_AREA;
		_delay_ms(1);
	}

	// �E������s
	executeRightTurn();
}

/*
 * ���H�G���A 8 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 7 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_08(void) {
	int counter = 0;
	int maxSpeed = BASE_SPEED_BY_TURF_AREA;
    int sensorPattern = BIT_111111;
	int findAnySensorCount = 0;

	// ���C�����r�؂��܂ł̓g���[�X����
	while (sensorPattern != BIT_000000) {
		traceCommon(&counter, &maxSpeed);
		sensorPattern = getSensorPattern();
		// �������Ȃ�
		maxSpeed = BASE_SPEED_BY_TURF_AREA;
		_delay_ms(1);
	}

	// ��~���s
	//stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);

	StraightMove();
    _delay_ms(10);

	// �Z���T�[�̂����ꂩ�������肷��܂ŁA���i�p��
	while (1) {
		StraightMove();
		sensorPattern = getSensorPattern();

		// 3��A�����Ĕ����肵���烋�[�v�𔲂���
		if (sensorPattern != BIT_000000) {
			findAnySensorCount++;
			if (findAnySensorCount > 2) {
				break;
			}
		}
		_delay_ms(1);
	}

	// ������Ɛi��Œ�~
	adjustTurnPosition();

	// �E������s
	executeRightTurnFromOnLine();
	BaseSpeed = BASE_SPEED_INIT_VAL;
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
}

/*
 * ���H�G���A 9 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 8 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_09(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
		_delay_ms(1);
	}

	// �E������s
	executeRightTurn();
	BaseSpeed = BASE_SPEED_INIT_VAL;
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
	StopMove();//DBG
}

/*
 * ���H�G���A 10 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 9 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_10(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��~���s
	stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 11 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 10 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_11(void) {
	int sensorPattern = BIT_000000;
	int findAnySensorCount = 0;

	// �Z���T�[�̂����ꂩ�������肷��܂ŁA���i�p��
	while (1) {
		StraightMove();
		sensorPattern = getSensorPattern();
		// 3��A�����Ĕ����肵���烋�[�v�𔲂���
		if (sensorPattern != BIT_000000) {
			findAnySensorCount++;
			if (findAnySensorCount > 2) {
				break;
			}
		}
		_delay_ms(1);
	}

	// ��~���s
	StopMove();

	// �Z���T�[�l�ɉ����Đ�������s
	// TODO:����

	// ����I����A��~���s
	stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 12 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 11 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_12(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��~���s
	StopMove();
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 13 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 12 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_13(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (counter > 1500) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��~���s
	StopMove();
	initSensorHistory();
	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 14 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 13 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_14(void) {
}

/*
 * ���H�G���A 15 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 14 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_15(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 16 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 15 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
 void traceBackwardArea_16(void) {
	int counter = 0;
	int maxSpeed = BASE_SPEED_INIT_VAL;
	int sensorPattern = BIT_111111;
	int findAnySensorCount = 0;

	// ���C�����r�؂��܂ł̓g���[�X����
	while (sensorPattern != BIT_000000) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��~���s
	StopMove();

	// �Z���T�[�̂����ꂩ�������肷��܂ŁA���i�p��
	while (1) {
		StraightMove();
		sensorPattern = getSensorPattern();

		// 3��A�����Ĕ����肵���烋�[�v�𔲂���
		if (sensorPattern != BIT_000000) {
			findAnySensorCount++;
			if (findAnySensorCount > 2) {
				break;
			}
		}
	}

	// ��~���s
	StopMove();

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ���H�G���A 17 �̃g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�Ȃ��i���H�G���A 16 �̃g���[�X���삩��p���j�B
 *   �I�������F
 */
void traceBackwardArea_17(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// �E������s
	currentTraceAction = executeRightTurn();
	//setSensorHistory(executeRightTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
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
		sensorPattern == BIT_111000) {
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

/*
 * ��1�̏ꍇ�̍����񌟏o�p�g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�O��̃g���[�X���삩��p���B
 *   �I�������F�Z���T�ō��^�[�������o���Ē��p���񂪊�������B
 */
 void shortTraceToLeftTurn(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_L_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// ��������s
	currentTraceAction = executeLeftTurn();
	//setSensorHistory(executeLeftTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ��1�̏ꍇ�̉E���񌟏o�p�g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�O��̃g���[�X���삩��p���B
 *   �I�������F�Z���T�ŉE�^�[�������o���Ē��p���񂪊�������B
 */
 void shortTraceToRightTurn(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	while (currentTraceAction != TRACE_R_TURN) {
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// �E������s
	currentTraceAction = executeRightTurn();
	//setSensorHistory(executeRightTurn());
	BaseSpeed = BASE_SPEED_INIT_VAL;
}

/*
 * ��2���擾��̌�ޗp�g���[�X����
 * @return �Ȃ�
 * @condition
 *   �J�n�����F�O��̃g���[�X���삩��p���B
 *   �I�������F�Z���T�ŉE�^�[�������o���Ē�~����������B
 */
void traceBackLowMoveArea_01(void) {
	BaseSpeed = BASE_SPEED_BY_TURF_AREA;
	int sensorPattern = BIT_111111;

	// (�ŏ�̃o�b�N�j�Z���T�[���O�����肷��܂ŁA��ތp��
	while (sensorPattern != BIT_000000) {
		BackLowMove();
		sensorPattern = getSensorPattern();
		_delay_ms(1);
	}

	// �m���ɐ����痣��邽�߁A�����Ō�i����
	BackLowMove();
	_delay_ms(300);

	BaseSpeed = SLOW_BACK_VAL;
	// �i�v���_����̃o�b�N�j�Z���T�[�̂����ꂩ�������肷��܂ŁA��ތp��
	while (sensorPattern == BIT_000000) {
		BackLowMove();
		sensorPattern = getSensorPattern();
		_delay_ms(1);
	}

	// ��~���s
    stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);

	// �x�[�X���x��0�ɐݒ�
	BaseSpeed = 0;

	//�E������s
	executeRightTurn();

	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;
}
