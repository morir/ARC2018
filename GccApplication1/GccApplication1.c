//##########################################################
//##                      R O B O T I S                   ##
//## CM-700 (Atmega2561) Example code for Dynamixel.      ##
//##                                           2009.11.10 ##
//##########################################################

#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include "SerialManager.h"
#include "include/dynamixel.h"
#include "SensorManager.h"
#include "MotorManager.h"
#include "DebugLog.h"
#include "AvrTimer.h"
#include "ArmActionManager.h"
#include "TraceManager.h"
#include "TracePatternManager.h"
#include "TurnManager.h"

// ------------------ Defined ------------------
// Line Sensor
#define LINE_STATE_BLACK    0//センサー値でラインが白判定
#define LINE_STATE_WHITE    1//センサー値でラインが黒判定

#define _LED_ON_

// ------------------ Method Definition ------------------
void execute2018PreExamination(void);

void treasureHunt_01(void);
void treasureHunt_02(void);
void treasureHunt_03(void);

void dumpTreasures(void);

void executeFinalAction(void);

void initEmergencyStop(void);

void sensorDebug(void);

void setLED(void);
void LED_on(int i);
void LED_off(int i);

// ------------------ Global Variables Definition ------------------

// Serial Message Buffer
int serCmd[SERIAL_BUFFER_SIZE] = {0};

int isSearchingLeft = 0;

// ------------------ Method ------------------

/**
* エントリーポイント
* @brief エントリーポイント
* @return 0：メイン処理の継続
* @return 1：メイン処理の終了
*/
int main(void) {

    initEmergencyStop();
    setLED();
    initIRSensor();
    MotorInit();
    initSerial();
	sensorDebug();//センサー値の確認だけをしたい場合、コメントアウトを解除
	Debug_AllMotorCurrentAngle();// 現在のモータ角度を表示(Debug用)

	initArmMotor();

    //2018年事前審査用動作実行
    execute2018PreExamination();

	FindFormation();

	LOG_DEBUG("Call ArmOpenFormation() %s\r\n", "");
	_delay_ms(2000);//1秒待つ⇒動作に合わせて変更してください
	ArmOpenFormation();
	
	LOG_DEBUG("Call CatchAndReleaseFormation() %s\r\n", ""); 
	_delay_ms(2000);//1秒待つ⇒動作に合わせて変更してください
	CatchAndReleaseFormation();

    // ゴール判定後の動作実質ここから開始？
	executeFinalAction();
	StopMove();
}

void execute2018PreExamination(void) {
	LOG_DEBUG("Call CatchAndReleaseFormation() %s\r\n", "");
}

void sensorDebug(void) {
	while(1) {
		getSensors();
		LOG_WARN("sensor %3d: %3d: %3d: %3d: %3d: %3d \r\n",
		IR[LEFT_OUTSIDE], IR[LEFT_CENTER], IR[LEFT_INSIDE],
		IR[RIGHT_INSIDE], IR[RIGHT_CENTER], IR[RIGHT_OUTSIDE]);
		LOG_WARN("IR[L %1d%1d%1d%1d%1d%1d R]\r\n",
		((IR[LEFT_OUTSIDE]  <= COMPARE_VALUE) ? 1 : 0),
		((IR[LEFT_CENTER]   <= COMPARE_VALUE) ? 1 : 0),
		((IR[LEFT_INSIDE]   <= COMPARE_VALUE) ? 1 : 0),
		((IR[RIGHT_INSIDE]  <= COMPARE_VALUE) ? 1 : 0),
		((IR[RIGHT_CENTER]  <= COMPARE_VALUE) ? 1 : 0),
		((IR[RIGHT_OUTSIDE] <= COMPARE_VALUE) ? 1 : 0));
		LOG_WARN("currentTraceAction %d\r\n", currentTraceAction);
		_delay_ms(500);
	}
}

/*
 * 宝物 1 のトレース動作
 * @return なし
 * @condition
 *   開始条件：なし（往路エリア 5 のトレース動作から継続）。
 *   終了条件：宝物（白）を回収、180度旋回が完了する。
 */
 void treasureHunt_01(void) {
    //int sensorPattern = BIT_000000;
    LOG_INFO("treasureHunt_01() %s\r\n", "1");

    int left = 0, center = 0, right = 0;
    int isFirst = 0;
    while (center <= 180) {
	    GetAXS1SensorFireData(&left, &center, &right);
        // 宝物検索用ライントレースを実行
        TreasureFindingLineTrace(isFirst);
	    isFirst++;
    }
    // 停止する
    StopMove();
    _delay_ms(500);

    // 手を開く
    ArmOpenFormation();

    // 前進or後進する（実動作に合わせて設定）。
    StraightLowMove2();
	/* 長すぎると、ペットボトルを倒すかも */
	_delay_ms(350);
	
    // 停止する
    StopMove();
    _delay_ms(1000);

    // 宝物を掴んで荷台に乗せる
    CatchAndReleaseFormation();

    // ライン上からの旋回を行う
    executeRightTurnFromOnLine();

    // 停止する
    StopMove();
    _delay_ms(100);
}

/*
 * 宝物 2 のトレース動作
 * @return なし
 * @condition
 *   開始条件：
 *   終了条件：宝物を発見して回収処理実行
 */
 void treasureHunt_02(void) {
    LOG_INFO("treasureHunt_02() %s\r\n", "1");

    //int left = 0, center = 0, right = 0;
    //GetAXS1SensorFireData(&left, &center, &right);
    //while (center <= 130) {
        //// 宝物検索用ライントレースを実行(旋回)
        //LeftTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
		//_delay_ms(1);
        //GetAXS1SensorFireData(&left, &center, &right);
    //}

    // 停止する
    StopMove();
    _delay_ms(500);
 
    // 手を開く
    ArmOpenFormation();
     	
    // 前進or後進する（実動作に合わせて設定）。
    StraightLowMove2();
    /* 長すぎると、ペットボトルを倒すかも */
    _delay_ms(350);

    // 停止する
    StopMove();
    _delay_ms(1000);

    // 宝物を掴んで荷台に乗せる
    CatchAndReleaseFormation();

    // 停止する
    StopMove();
    _delay_ms(100);
}

/*
 * 宝物 3 のトレース動作
 * @return なし
 * @condition
 *   開始条件：
 *   終了条件：
 */
 void treasureHunt_03(void) {
    LOG_INFO("treasureHunt_03() %s\r\n", "1");

    int left = 0, center = 0, right = 0;
    int isFirst = 0;
    while (center <= 180) {
        GetAXS1SensorFireData(&left, &center, &right);
        // 宝物検索用ライントレースを実行
        TreasureFindingLineTrace(isFirst);
        isFirst++;
    }
    // 停止する
    StopMove();
    _delay_ms(500);

    // 手を開く
    ArmOpenFormation();
	
	// 前進or後進する（実動作に合わせて設定）。
	StraightLowMove2();
	/* 長すぎると、ペットボトルを倒すかも */
	_delay_ms(350);
    
    // 停止する
    StopMove();
    _delay_ms(1000);

    // 宝物を掴んで荷台に乗せる
    CatchAndReleaseFormation();

    // ライン上からの旋回を行う
    executeRightTurnFromOnLine();

    // 停止する
    StopMove();
    _delay_ms(100);
}

/**
* ゴール到達時の処理
* @brief ゴール到達時の処理
* @return なし
*/
void executeFinalAction(void)
{
	LOG_INFO("executeFinalAction!!\r\n");
	StopMove();
	_delay_ms(1000);

	/* ゆっくり後進 */
	MotorControl(RIGHT_MOTOR, 40);
	MotorControl(LEFT_MOTOR, 1063);
	_delay_ms(500);//！要調整
	StopMove();//停止を実行
	_delay_ms(10);

	/* 200度くらい右回りで回転 */
	MotorControl(RIGHT_MOTOR, 75);
	MotorControl(LEFT_MOTOR, 75);
	_delay_ms(1200);//！要調整
	StopMove();
	_delay_ms(10);

	// 肩を前に出す
	MotorControlJoint(V_MOV_SHOULDER_MOTOR, 100, 600);
	_delay_ms(1000);//！要調整

	/* 荷台を傾けて宝物を落とす */
	dumpTreasures();
	_delay_ms(500);
	
	/* ゆっくり前進 */
	MotorControl(RIGHT_MOTOR, 1063);
	MotorControl(LEFT_MOTOR, 40);
	_delay_ms(500);
	StopMove();//停止を実行
}

/************************************************************************/
// 宝物を落とす
/************************************************************************/
void dumpTreasures(void) {
	_delay_ms(1000);//1秒待つ⇒動作に合わせて変更してください
	//MotorControlJoint( CARGO_BED_MOTOR, 30, 352 );//モーターを後方にゆっくり傾ける！要調整
	//_delay_ms(6000);//6秒継続
	//MotorControlJoint( CARGO_BED_MOTOR, 100, 512 );//モーターをセンター位置に戻す！要調整
	//_delay_ms(3000);//3秒待つ⇒動作に合わせて変更してください

}

void initEmergencyStop(void) {
    DDRD  = 0x70;
    PORTD = 0x11;
}

/**
 * LEDを設定
 * @brief LEDを設定
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */
void setLED(void) {
#ifdef _LED_ON_
	//マイコンのレジスタ(DDRC)の設定
    DDRC  = 0x7F;
	//マイコンの出力ポート(PORTC)の設定
    PORTC = 0x7F;
#endif // _LED_ON_
}

/**
 * LED点灯
 * @brief LED点灯
 * @param (int i) LEDの番号
 * @return なし
 */
void LED_on(int i) {
#ifdef _LED_ON_
    if (i < 1 || i > 6) return;
	unsigned char c = PORTC;
	//マイコンの出力ポート(PORTC)の設定
    PORTC = c^(1<<i);
#endif // _LED_ON_
}

/**
 * LED消灯
 * @brief LED消灯
 * @param (int i) LEDの番号
 * @return なし
 */
void LED_off(int i) {
#ifdef _LED_ON_
    if (i < 1 || i > 6) return;
	unsigned char c = PORTC;
	//マイコンの出力ポート(PORTC)の設定
    PORTC = ~(c^(1<<i));
#endif // _LED_ON_
}
