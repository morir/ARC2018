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
* センサー値のBitパターンを取得する。
* @brief センサー値を参照し、対応するアクションを取得する。
* @return 戻り値の説明
*/
int getSensorPattern(void) {
	// LEDを設定
	//setLED();
	
	// センサー値を取得
	getSensors();
	return IR_BitPattern;
}

/**
* Bitパターンの履歴を初期化する。
* @brief Bitパターンの履歴を直進のBitパターンで初期化する。
* @return 戻り値の説明
*/
void initSensorHistory(void) {
	memset(IR, 0, sizeof(IR));
	IR_BitPattern = BIT_000000;
	currentCount = 0;
	memset(IR_BitPatternHistory, IR_BitPattern, sizeof(IR_BitPatternHistory));
}

/**
 * センサー値を取得
 * @brief センサー値を取得
 * @return なし
 * @detail センサー値を取得し、IR[]およびIR_BitPatternを更新する。
 */
void getSensors(void) {
	/* 現在のカウンタ値を更新 */
    currentCount = ((currentCount + 1) % HISTORY_MAXSIZE);
	/* センサー値を取得 */
    ReadIRSensors(IR);
	
	/* IR状態をBITパターンに変換 */
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

