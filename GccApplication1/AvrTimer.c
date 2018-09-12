/**
 * @file AvrTimer.h
 * @brief AVR�^�C�}���䕔
 * @author f.aimano
 * @date 2017/10/20
 * @see http://threesons-technicalmemo.blogspot.jp/2014/03/avr16.html
 * @detail CM-700��CPU��Atmel��ATMega2561����������Ă���B
 * ATMega2561�̃N���b�N��16MHz�B
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/common.h>

#include "AvrTimer.h"
#include "DebugLog.h"
#include "MovingDistance.h"
#include "MotorManager.h"

extern int getSensorPatternCalledFromTimer(void);

#define F_CPU_DIV1000	(16000L)	// 16MHz
#define DIVIDE			(8L)		// �����i���/����1����ڼ޽�B�̐ݒ�Ƒ��ւ���j

volatile static uint32_t avr16bitMTimer = 0;	// Avr��16bit�^�C�}�̌o�ߎ���(msec)

/**
 * AVR�^�C�}�J�n
 * @brief AVR�^�C�}�J�n
 */
void AvrTimerStart() {
	avr16bitMTimer = 0;
 
	//���荞�݋֎~
	cli();
 
	//���/����1����ڼ޽�A�̐ݒ�
	//�i�^�C�}�p�s���Ƃ��Ďg��Ȃ��j
	TCCR1A = 0x00; //�^�C�}�֌W�̃s���͕W���|�[�g����Ƃ���
 
	//���/����1����ڼ޽�B�̐ݒ�
	TCCR1B = (0<<CS12)|(1<<CS11)|(0<<CS10);	// 1/8�����Ń^�C�}ON
 
	//���/����1���荞��Ͻ� ڼ޽��ݒ�
	TIMSK1 = (1<<TOIE1);//�^�C�}�P�I�[�o�[�t���[���荞�݋���
 
	//���荞�݋���
	sei();
}
 
/**
 * AVR�^�C�}�擾
 * @brief AVR�^�C�}�擾(�~���b)
 * @attention ISR(TIMER1_OVF_vect) ���ł̃R�[���͋֎~�B
 */
uint32_t AvrTimerGet() {
	//16�r�b�g���W�X�^�̓ǂݏ����̍ۂɂ́A�e���|�������W�X�^���g�p����B
	//���̂��߁A���荞�݋֎~���삪�K�v�B
 
	return avr16bitMTimer;
}
 
/**
 * AVR�^�C�}�I��
 * @brief AVR�^�C�}�I��
 */
void AvrTimerEnd() {
	uint8_t sreg;
	sreg = SREG;
	cli();
 
	//�^�C�}��0�ɂ���
	TCNT1 = 0;
	SREG = sreg;
 
	//�o�ߎ��Ԃ�0�ɂ���
	avr16bitMTimer = 0;
}
 
/**
 * AVR�^�C�}������
 * @brief AVR�^�C�}������
 */
void AvrTimerReset() {
	TCCR1B = 0;//�^�C�}off 
}

/**
 * TIMER1_OVF_vect�̃^�C�}���荞��
 * @brief TIMER1_OVF_vect�̃^�C�}���荞��
 * @attention �{���\�b�h�����������s���̂͋֎~�B�������~�܂�܂��B
 * �Estdio (printf, putc, getc, etc),
 * �Emalloc
 * �Enew
 */
ISR(TIMER1_OVF_vect) {
	avr16bitMTimer += (65536L * DIVIDE)/ F_CPU_DIV1000;
}