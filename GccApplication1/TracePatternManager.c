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
	//memset(IR, 0, sizeof(IR));
	//IR_BitPattern = BIT_000000;
	//currentCount = 0;
	//memset(IR_BitPatternHistory, IR_BitPattern, sizeof(IR_BitPatternHistory));
}

/**
 * センサー値を取得
 * @brief センサー値を取得
 * @return なし
 * @detail センサー値を取得し、IR[]およびIR_BitPatternを更新する。
 */
void getSensors(void) {

}

