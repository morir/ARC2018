/*
 * TurnManager.c
 *
 * Created: 2017/10/28 22:37:52
 *  Author: Administrator
 */
 
#include "SensorManager.h"
#include "MotorManager.h"
#include "TurnManager.h"
#include "TracePatternManager.h"

extern void adjustTurnPosition(void);
extern void LED_on(int i);
extern void stopMoveLessThanVal(int val);

 /**
 * �����񓮍�̏���������
 * ��~�����s���āA
 * ��ȉ��̑��x�܂Ō����ł�����A������̃X�e�[�^�X��Ԃ�
 */
int initLeftTurnAction(int referenceVal) {

	StopMove();//��~�����s
	int judgeSpeed = 0;
	while(1) {
		judgeSpeed = GetCurrentSpeedR();//���[�^�[�̑��x���擾
		if( (judgeSpeed >= 0 && judgeSpeed <= referenceVal) ||
			(judgeSpeed >= 1024 && judgeSpeed <= (1024 + referenceVal)) ) {
			//���x��maxVal�ȉ��Ȃ�stop()������
			return TRACE_L_TURN;
		}
	}
}

/**
 * �E���񓮍�̏�����
 * ��~�����s���āA
 * ��ȉ��̑��x�܂Ō����ł�����A�E����̃X�e�[�^�X��Ԃ�
 */
int initRightTurnAction(int referenceVal) {

	StopMove();//��~�����s
	int judgeSpeed = 0;
	while(1) {
		judgeSpeed = GetCurrentSpeedR();//���[�^�[�̑��x���擾
		if( (judgeSpeed >= 0 && judgeSpeed <= referenceVal) ||
			(judgeSpeed >= 1024 && judgeSpeed <= (1024 + referenceVal)) ) {
			//���x��maxVal�ȉ��Ȃ�stop()������
			return TRACE_R_TURN;
		}
	}
}

/**
 * ��������s
 * ���񓮍�������āA�Z���T�[�������ɂȂ����璼�i���w�肵�Ĕ�����
 */
int executeLeftTurn(void){
	int sensorPattern = BIT_000000;

	//���񔻒肳�ꂽ���~�����s
	initLeftTurnAction(STOP_JUDGE_MAX_LIMIT);
	LED_on(1);

	//��~���m�肵����x�[�X���x�ɉ����āA�O�ior��i�����s
	adjustTurnPosition();

	// ��������s
    LeftTurnMove();
	while(1) {
		sensorPattern = getSensorPattern();

		//���񓮍�𔲂��邽�߂̏����𔻒�
		if (
			//sensorPattern == BIT_010000 || sensorPattern == BIT_011000 ||
			sensorPattern == BIT_011100 || sensorPattern == BIT_001110 ||
			sensorPattern == BIT_001000 || sensorPattern == BIT_001100 ||
			sensorPattern == BIT_000100 || sensorPattern == BIT_000110 ||
			sensorPattern == BIT_000010
			) {
			LED_on(2);
			//�����̃Z���T�[�����Ȃ��~�����s
			stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
			break;
		}

   	    //���Z���T�[�����o���Ă��邩�m�F����
   	    if (sensorPattern == BIT_100000) {
       	    //���Z���T�[�����o��������񑬓x�𗎂Ƃ�
       	    LeftTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
   	    }
	}

	//�����~�����̎~�܂����ʒu�ŃZ���T�[�������S�̂����ꂩ�Ȃ�t����I��
	sensorPattern = getSensorPattern();
	//if (sensorPattern == BIT_010000) {
	    ////���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
	    //return TRACE_L_ROUND_MIDDLE;
	//} else if (sensorPattern == BIT_011000) {
	    ////���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
	    //return TRACE_L_ROUND_SOFT;
	//} else if (sensorPattern == BIT_001000) {
		////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
	    //return TRACE_STRAIGHT;
	//} else if (sensorPattern == BIT_011100) {
		////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
		//return TRACE_STRAIGHT;
	//} else if (sensorPattern == BIT_001100) {
		////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
	    //return TRACE_STRAIGHT;
	//} else if (sensorPattern == BIT_001110) {
		////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
		//return TRACE_STRAIGHT;
	//} else if (sensorPattern == BIT_000100) {
		////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
	    //return TRACE_STRAIGHT;
	//} else if (sensorPattern == BIT_000110) {
	    ////�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
	    //return TRACE_R_ROUND_SOFT;
	//} else if (sensorPattern == BIT_000010) {
	    ////�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
	    //return TRACE_R_ROUND_MIDDLE;
	//}
	if ((sensorPattern == BIT_010000) ||
		(sensorPattern == BIT_011000) ||
		(sensorPattern == BIT_001000) ||
		(sensorPattern == BIT_011100) ||
		(sensorPattern == BIT_001100) ||
		(sensorPattern == BIT_001110) ||
		(sensorPattern == BIT_000100) ||
		(sensorPattern == BIT_000110) ||
		(sensorPattern == BIT_000010)) {
		return sensorPattern;
	}
	
	LED_on(3);
	//�Z���T�[�𒆉��ɖ߂����ߒx����������s
	RightTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
	while(1) {
		//�t���񓮍�𔲂��邽�߂̏����𔻒�
		sensorPattern = getSensorPattern();
		if (sensorPattern == BIT_001000 || sensorPattern == BIT_001100 || sensorPattern == BIT_000100) {
			stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
			//return TRACE_STRAIGHT;
			return BIT_000000;
		} else if ( sensorPattern == BIT_010000 ||	sensorPattern == BIT_011000 ||
					sensorPattern == BIT_100000 ||	sensorPattern == BIT_110000 ) {
			//���ɋt���܂Ő��񂵂Ă�����i�z��������������ł��Ă��܂����ꍇ�Ȃǁj
	        //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
            
	        //return TRACE_L_ROUND_MIDDLE;
			return BIT_010000;
		}
	}

	//�ēx�Z���T�[�𒆉��ɖ߂����ߒx����������s�i�����܂ł͎��s����Ȃ��z��j
	LED_on(4);
	LeftTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
	while(1) {
		//�t���񓮍�𔲂��邽�߂̏����𔻒�
		sensorPattern = getSensorPattern();
		if (sensorPattern == BIT_001000 || sensorPattern == BIT_001100 || sensorPattern == BIT_000100) {
			stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
			//return TRACE_STRAIGHT;
			return BIT_000000;
		}
	}
	//return TRACE_STRAIGHT;
	return BIT_000000;

}

/**
 * �E������s
 * ���񓮍�������āA�Z���T�[�������ɂȂ����璼�i���w�肵�Ĕ�����
 */
int executeRightTurn(void){
	int sensorPattern = BIT_000000;

	//���񔻒肳�ꂽ���~�����s
	initRightTurnAction(STOP_JUDGE_MAX_LIMIT);
	LED_on(1);

	//��~���m�肵����x�[�X���x�ɉ����āA�O�ior��i�����s
	adjustTurnPosition();

	// �E������s
	RightTurnMove();
	while(1) {
		sensorPattern = getSensorPattern();

		//���񓮍�𔲂��邽�߂̏����𔻒�
		if (
			//sensorPattern == BIT_000010 || sensorPattern == BIT_000110 ||
			sensorPattern == BIT_011100 || sensorPattern == BIT_001110 ||
			sensorPattern == BIT_000100 || sensorPattern == BIT_001100 ||
			sensorPattern == BIT_001000 || sensorPattern == BIT_011000 ||
			sensorPattern == BIT_010000
		    ) {
			LED_on(2);
			//�����̃Z���T�[�����Ȃ��~�����s
			stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
			break;
		}
   	    //�E�Z���T�[�����o���Ă��邩�m�F����
   	    if (sensorPattern == BIT_000001) {
       	    //�E�Z���T�[�����o��������񑬓x�𗎂Ƃ�
       	    RightTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
   	    }
	}

	//�����~�����̎~�܂����ʒu�ŃZ���T�[�������Ȃ�t����I��
    sensorPattern = getSensorPattern();
    //if (sensorPattern == BIT_000010) {
        ////���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
        //return TRACE_R_ROUND_MIDDLE;
    //} else if (sensorPattern == BIT_000110) {
        ////���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
        //return TRACE_R_ROUND_SOFT;
    //} else if (sensorPattern == BIT_000100) {
        ////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        //return TRACE_STRAIGHT;
    //} else if (sensorPattern == BIT_001110) {
        ////���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
        //return TRACE_R_ROUND_SOFT;
    //} else if (sensorPattern == BIT_001100) {
        ////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        //return TRACE_STRAIGHT;
    //} else if (sensorPattern == BIT_011100) {
        ////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        //return TRACE_STRAIGHT;
    //} else if (sensorPattern == BIT_001000) {
        ////�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        //return TRACE_STRAIGHT;
    //} else if (sensorPattern == BIT_011000) {
        ////�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
        //return TRACE_L_ROUND_SOFT;
    //} else if (sensorPattern == BIT_010000) {
        ////�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
        //return TRACE_L_ROUND_MIDDLE;
    //}
	if ((sensorPattern == BIT_000010) ||
		(sensorPattern == BIT_000110) ||
		(sensorPattern == BIT_000100) ||
		(sensorPattern == BIT_001110) ||
		(sensorPattern == BIT_001100) ||
		(sensorPattern == BIT_011100) ||
		(sensorPattern == BIT_001000) ||
		(sensorPattern == BIT_011000) ||
		(sensorPattern == BIT_010000)) {
			return sensorPattern;
	}
	
	LED_on(3);
	//�Z���T�[�𒆉��ɖ߂����ߒx����������s
	LeftTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
	while(1) {
		//�t���񓮍�𔲂��邽�߂̏����𔻒�
		sensorPattern = getSensorPattern();
		if (sensorPattern == BIT_001000 || sensorPattern == BIT_001100 || sensorPattern == BIT_000100) {
			stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
			//return TRACE_STRAIGHT;
			return BIT_000000;
		} else if ( sensorPattern == BIT_000110 || sensorPattern == BIT_000010 ||
					sensorPattern == BIT_000011 || sensorPattern == BIT_000001 ) {
			//���ɋt���܂Ő��񂵂Ă�����i�z��������������ł��Ă��܂����ꍇ�j
	        //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
	        //return TRACE_R_ROUND_MIDDLE;
			return BIT_000010;
		}
	}
		
	//�ēx�Z���T�[�𒆉��ɖ߂����ߒx����������s�i�����܂ł͎��s����Ȃ��z��j
	LED_on(4);
	RightTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
	while(1) {
		//�t���񓮍�𔲂��邽�߂̏����𔻒�
		sensorPattern = getSensorPattern();
		if (sensorPattern == BIT_001000 || sensorPattern == BIT_001100 || sensorPattern == BIT_000100) {
			stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
			return BIT_000000;
		}
	}
	//return TRACE_STRAIGHT;
	return BIT_000000;
}

/************************************************************************/
// �g���[�X���C���ォ��̍�������s���B
// ���s�O�ɑ��s���[�^���~���Ă������ƁB
// �����A�����̃Z���T�[���g���[�X���C�������o�����珈�����I������B
/************************************************************************/
void executeLeftTurnFromOnLine(void) {
    int sensorPattern = BIT_000000;

    // ��������s
    LeftTurnMove();
    
    // ����J�n���Ƀ��C���Z���T�[�����C����ǂݎ��ʒu�ɋ���͂��Ȃ̂�
    // �Z���T�[�����C���O�܂Œʉ߂��Ă��邱�Ƃ��m�F����B
    while(1) {
        sensorPattern = getSensorPattern();

        //�E�Z���T�[�����o���Ă��邩�m�F����
        if (sensorPattern == BIT_000001) {
            // ������p�����Ĕ�����i�ł���΂����Ŋm���ɔ��������j
            _delay_ms(300);//�Z���T�[���S�Ēʉ߂���܂Ő���
            break;
            } else if (sensorPattern == BIT_000010) {
            // ������p�����Ĕ�����
            _delay_ms(500);//�Z���T�[���S�Ēʉ߂���܂Ő���
            break;
            } else if (sensorPattern == BIT_000110) {
            // ������p�����Ĕ�����i�\���j
            //_delay_ms(100);
            //break;
        }
        //_delay_ms(10);//���[�v�̑҂����Ԃ�K�v�ɉ����Đݒ�
    }
    
    // ���񓮍�̕��A����
    while(1) {
        sensorPattern = getSensorPattern();

        //���񓮍�𔲂��邽�߂̏����𔻒�
        if (
        sensorPattern == BIT_011100 || sensorPattern == BIT_001110 ||
        sensorPattern == BIT_001000 || sensorPattern == BIT_001100 ||
        sensorPattern == BIT_000100 || sensorPattern == BIT_000110
        ) {
            LED_on(2);
            //�����̃Z���T�[�����Ȃ��~�����s
            stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
            break;
        }

        //���Z���T�[�����o���Ă��邩�m�F����
        if (sensorPattern == BIT_100000) {
            //���Z���T�[�����o��������񑬓x�𗎂Ƃ�
            LeftTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
        }
    }
    
    //�����~�����̎~�܂����ʒu�ŃZ���T�[�������S�̂����ꂩ�Ȃ�t����I��
    sensorPattern = getSensorPattern();
    if (sensorPattern == BIT_010000) {
        //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_L_ROUND_MIDDLE);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_011000) {
        //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_L_ROUND_SOFT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_001000) {
        //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        Execute(TRACE_STRAIGHT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_001100) {
        //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        Execute(TRACE_STRAIGHT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_000100) {
        //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        Execute(TRACE_STRAIGHT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_000110) {
        //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_R_ROUND_SOFT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_000010) {
        //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_R_ROUND_MIDDLE);
        _delay_ms(50);
        return;
    }
    
    // �����~���蒆�ɃZ���T�[�����C����ʂ�z�����z��
    //�Z���T�[�𒆉��ɖ߂����ߒx����������s
    RightTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
    while(1) {
        sensorPattern = getSensorPattern();

        //���񓮍�𔲂��邽�߂̏����𔻒�
        // ���x�͗����邪�A�Ƃ肠��������𔲂���
        if (sensorPattern == BIT_000010) {
            //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_R_ROUND_MIDDLE);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_000110) {
            //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_R_ROUND_SOFT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_000100) {
            //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
            Execute(TRACE_STRAIGHT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_001100) {
            //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
            Execute(TRACE_STRAIGHT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_001000) {
            //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
            Execute(TRACE_STRAIGHT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_011000) {
            //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_L_ROUND_SOFT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_010000) {
            //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_L_ROUND_MIDDLE);
            _delay_ms(50);
            return;
        }
    }

    // ������߂Ē��i�Ŕ�����
    Execute(TRACE_STRAIGHT);
    _delay_ms(20);
    return;
}

/************************************************************************/
// �g���[�X���C���ォ��̉E������s���B
// ���s�O�ɑ��s���[�^���~���Ă������ƁB
// �����A�����̃Z���T�[���g���[�X���C�������o�����珈�����I������B
/************************************************************************/
void executeRightTurnFromOnLine(void) {
    int sensorPattern = BIT_000000;

    // ��������s
    RightTurnMove();
    
    // ����J�n���Ƀ��C���Z���T�[�����C����ǂݎ��ʒu�ɋ���͂��Ȃ̂�
    // �Z���T�[�����C���O�܂Œʉ߂��Ă��邱�Ƃ��m�F����B
    while(1) {
        sensorPattern = getSensorPattern();

        //�E�Z���T�[�����o���Ă��邩�m�F����
        if (sensorPattern == BIT_100000) {
            // ������p�����Ĕ�����i�ł���΂����Ŋm���ɔ��������j
            _delay_ms(300);//�Z���T�[���S�Ēʉ߂���܂Ő���
            break;
            } else if (sensorPattern == BIT_010000) {
            // ������p�����Ĕ�����
            _delay_ms(500);//�Z���T�[���S�Ēʉ߂���܂Ő���
            break;
            } else if (sensorPattern == BIT_011000) {
            // ������p�����Ĕ�����i�\���j
            //_delay_ms(100);
            //break;
        }
        //_delay_ms(10);//���[�v�̑҂����Ԃ�K�v�ɉ����Đݒ�
    }
    
    // ���񓮍�̕��A����
    while(1) {
        sensorPattern = getSensorPattern();

        //���񓮍�𔲂��邽�߂̏����𔻒�
        if (
        sensorPattern == BIT_001110 || sensorPattern == BIT_011100 ||
        sensorPattern == BIT_000100 || sensorPattern == BIT_001100 ||
        sensorPattern == BIT_001000 || sensorPattern == BIT_011000
        ) {
            LED_on(2);
            //�����̃Z���T�[�����Ȃ��~�����s
            stopMoveLessThanVal(STOP_JUDGE_MAX_LIMIT);
            break;
        }

        //�E�Z���T�[�����o���Ă��邩�m�F����
        if (sensorPattern == BIT_000001) {
            //�E�Z���T�[�����o��������񑬓x�𗎂Ƃ�
            RightTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
        }
    }
    
    //�����~�����̎~�܂����ʒu�ŃZ���T�[�������S�̂����ꂩ�Ȃ�t����I��
    sensorPattern = getSensorPattern();
    if (sensorPattern == BIT_000010) {
        //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_L_ROUND_MIDDLE);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_011000) {
        //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_L_ROUND_SOFT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_001000) {
        //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        Execute(TRACE_STRAIGHT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_001100) {
        //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        Execute(TRACE_STRAIGHT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_000100) {
        //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
        Execute(TRACE_STRAIGHT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_000110) {
        //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_R_ROUND_SOFT);
        _delay_ms(50);
        return;
        } else if (sensorPattern == BIT_000010) {
        //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
        Execute(TRACE_R_ROUND_MIDDLE);
        _delay_ms(50);
        return;
    }
    
    // �����~���蒆�ɃZ���T�[�����C����ʂ�z�����z��
    //�Z���T�[�𒆉��ɖ߂����ߒx����������s
    RightTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
    while(1) {
        sensorPattern = getSensorPattern();

        //���񓮍�𔲂��邽�߂̏����𔻒�
        // ���x�͗����邪�A�Ƃ肠��������𔲂���
        if (sensorPattern == BIT_000010) {
            //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_R_ROUND_MIDDLE);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_000110) {
            //�E�Z���T�[�Ȃ̂ŁA�E�Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_R_ROUND_SOFT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_000100) {
            //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
            Execute(TRACE_STRAIGHT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_001100) {
            //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
            Execute(TRACE_STRAIGHT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_001000) {
            //�����Z���T�[�Ȃ̂ŁA���i�ɐݒ肵�Ĕ�����
            Execute(TRACE_STRAIGHT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_011000) {
            //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_L_ROUND_SOFT);
            _delay_ms(50);
            return;
            } else if (sensorPattern == BIT_010000) {
            //���Z���T�[�Ȃ̂ŁA���Ȃ�ɐݒ肵�Ĕ�����
            Execute(TRACE_L_ROUND_MIDDLE);
            _delay_ms(50);
            return;
        }
    }

    // ������߂Ē��i�Ŕ�����
    Execute(TRACE_STRAIGHT);
    _delay_ms(20);
    return;
}

/**
 * ����ɓ������x�[�X���x�ɉ����āA�ʒu�𒲐�����B
 * 2017���{�ɍ��킹�Ē����K�v�I
 */
void adjustTurnPosition(void) {
	if (BaseSpeed <= 45 ) {
		StraightLowMove();
		_delay_ms(220);	// 300ms �Ԋu���󂯂�
	} else if (BaseSpeed <= 80 ) {
		StraightLowMove();
		_delay_ms(200);	// 270ms �Ԋu���󂯂�
	} else if (BaseSpeed <= 100 ) {
		StraightLowMove();
		_delay_ms(170);	// 270ms �Ԋu���󂯂�
	} else if (BaseSpeed <= 120 ) {
		StraightLowMove();
		_delay_ms(140);	// 240ms �Ԋu���󂯂�
	} else if (BaseSpeed <= 140 ) {
		StraightLowMove();
		_delay_ms(130);	// 190ms �Ԋu���󂯂�
	} else if (BaseSpeed <= 160 ) {
		StraightLowMove();
		_delay_ms(110);	// 160ms �Ԋu���󂯂�
	} else if (BaseSpeed <= 180 ) {
		StraightLowMove();
		_delay_ms(100);	// 140ms �Ԋu���󂯂�
	} else {
		StraightLowMove();
		_delay_ms(80);	// 120ms �Ԋu���󂯂�
	}

    StopMove();
}


