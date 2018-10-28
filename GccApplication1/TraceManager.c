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
 * 共通トレース動作
 * @return なし
 * @condition
 *   開始条件：スタートコマンドを受信する。
 *   終了条件：センサで左ターンを検出して直角旋回が完了する。
 */
void traceCommon(int *counter, int *maxSpeed) {
	// センサー値を取得
	getSensors();
	if (currentTraceAction == TRACE_UNDEFINED) {
		_delay_ms(2);// delayTimeの間隔を空ける
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
	_delay_ms(1);// delayTimeの間隔を空ける
}

/*
 * 復路エリア 18 のトレース動作
 * @return なし
 * @condition
 *   開始条件：なし（復路エリア 17 のトレース動作から継続）。
 *   終了条件：ゴールエリアを検出して終了動作が完了する。
 */
void traceBackwardArea_18(void) {
	int counter = 0;
	int maxSpeed = MAX_SPEED;

	// 直進
	currentTraceAction = TRACE_STRAIGHT;
	BaseSpeed = BASE_SPEED_INIT_VAL;

	// AVRタイマ開始
	AvrTimerStart();

	// 移動距離の計測を開始
	StartMeasuringMovingDistance();

	// 目標の距離まで前進
	//currentTraceAction = TRACE_STRAIGHT;
	int32_t targetDistance = 110;	//目標距離 = 130cm
	while (targetDistance > GetMovingDistance()) {
		// 移動距離を更新
		UpdateMovingDistance();

		// 共通トレース動作
		traceCommon(&counter, &maxSpeed);
		counter++;
	}

	// 移動距離の計測を停止
	StopMeasuringMovingDistance();
	_delay_ms(10);

	// AVRタイマ停止
	AvrTimerEnd();
	AvrTimerReset();

	// 停止実行
	StopMove();
}

/*
 * 左右大き目にロボットを揺らしたジグザグなライントレースを実行
 */
void TreasureFindingLineTrace(int isFirst) {
	int sensorPattern = BIT_000000;
	BaseSpeed = 50;

	sensorPattern = getSensorPattern();

	// 初回動作の場合
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
		// ラインの右側サーチ中に左ラインを検出したら、
		// ラインの左側サーチに切り替える
		isSearchingLeftSide = 1;
		Execute(TRACE_L_TRESURE_FIND);
	} else if (
	    (isSearchingLeftSide > 0) &&
	    (sensorPattern == BIT_000010 ||
	    sensorPattern == BIT_000100 ||
	    sensorPattern == BIT_000110 ||
	    sensorPattern == BIT_001110
	    )) {
		// ラインの左側サーチ中に右ラインを検出したら、
		// ラインの右側サーチに切り替える
		isSearchingLeftSide = 0;
		Execute(TRACE_R_TRESURE_FIND);
	}
	
	_delay_ms(10);
}

