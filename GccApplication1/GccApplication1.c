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
void executeMission(void);
void getInputKey(int *outInputKey);
void executeFunction(int inpurKey);

void treasureHunt_01(void);
void treasureHunt_02(void);
void treasureHunt_03(void);
void TreasureFindingZigZagMove(int *counter);
void TargetFindingMove(void);

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
static long m_MoveCounter = 0;
static int m_MoveDirerctionFlag = 0;

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
    //timer_init();
    initIRSensor();

    MotorInit();
    initSerial();
    //sei();	// Interrupt Enable
	//sensorDebug();//センサー値の確認だけをしたい場合、コメントアウトを解除
	//Debug_AllMotorCurrentAngle();// 現在のモータ角度を表示(Debug用)

	initArmMotor();

    executeMission();
}

void sensorDebug(void) {
    int left = 0, center = 0, right = 0;
    while(1) {
        //getSensors();
        getIrSensor();
        LOG_WARN("sensor %3d: %3d: %3d: %3d: %3d: %3d \r\n",
        IRArrays[ADC_PORT_1], IRArrays[ADC_PORT_2], IRArrays[ADC_PORT_3],
        IRArrays[ADC_PORT_4], IRArrays[ADC_PORT_5], IRArrays[ADC_PORT_6]);

		GetAXS1SensorFireData(&left, &center, &right);
		LOG_WARN("GetAXS1SensorFireData() [%4d, %4d, %4d]\n\n", left, center, right);

        _delay_ms(500);

    }
}


void executeMission(void)
{
    int inputKey = INPUT_KEY_NONE;
    while(1) {
        // リモート操作を受け付けて処理を実行する。
        getInputKey(&inputKey);
        executeFunction(inputKey);
        _delay_ms(500);
    }
}

void getInputKey(int *outInputKey)
{
    int inpurKey = INPUT_KEY_NONE;
    switch (inpurKey) {
        case INPUT_KEY_UP:
            LOG_INFO("INPUT_KEY_UP\r\n");
            *outInputKey = INPUT_KEY_UP;
            break;
        case INPUT_KEY_DOWN:
            LOG_INFO("INPUT_KEY_DOWN\r\n");
            *outInputKey = INPUT_KEY_DOWN;
            break;
        case INPUT_KEY_LEFT:
            LOG_INFO("INPUT_KEY_LEFT\r\n");
            *outInputKey = INPUT_KEY_LEFT;
            break;
        case INPUT_KEY_RIGHT:
            LOG_INFO("INPUT_KEY_RIGHT\r\n");
            *outInputKey = INPUT_KEY_RIGHT;
            break;
        case INPUT_KEY_NONE:
            LOG_INFO("INPUT_KEY_NONE\r\n");
            *outInputKey = INPUT_KEY_NONE;
            break;
        case INPUT_KEY_ACTION_01:
            LOG_INFO("INPUT_KEY_ACTION_01\r\n");
            *outInputKey = INPUT_KEY_ACTION_01;
            break;
        case INPUT_KEY_ACTION_02:
            LOG_INFO("INPUT_KEY_ACTION_02\r\n");
            *outInputKey = INPUT_KEY_ACTION_02;
            break;
        case INPUT_KEY_ACTION_03:
            LOG_INFO("INPUT_KEY_ACTION_03\r\n");
            *outInputKey = INPUT_KEY_ACTION_03;
            break;
        case INPUT_KEY_ACTION_04:
            LOG_INFO("INPUT_KEY_ACTION_04\r\n");
            *outInputKey = INPUT_KEY_ACTION_04;
            break;
        case INPUT_KEY_ACTION_05:
            LOG_INFO("INPUT_KEY_ACTION_05\r\n");
            *outInputKey = INPUT_KEY_ACTION_05;
            break;
        case INPUT_KEY_ACTION_06:
            LOG_INFO("INPUT_KEY_ACTION_06\r\n");
            *outInputKey = INPUT_KEY_ACTION_06;
            break;
        case INPUT_KEY_ACTION_07:
            LOG_INFO("INPUT_KEY_ACTION_07\r\n");
            *outInputKey = INPUT_KEY_ACTION_07;
            break;
        case INPUT_KEY_ACTION_08:
            LOG_INFO("INPUT_KEY_ACTION_08\r\n");
            *outInputKey = INPUT_KEY_ACTION_08;
            break;
        case INPUT_KEY_ACTION_09:
            LOG_INFO("INPUT_KEY_ACTION_09\r\n");
            *outInputKey = INPUT_KEY_ACTION_09;
            break;
        case INPUT_KEY_ACTION_10:
            LOG_INFO("INPUT_KEY_ACTION_10\r\n");
            *outInputKey = INPUT_KEY_ACTION_10;
            break;
        case INPUT_KEY_ACTION_11:
            LOG_INFO("INPUT_KEY_ACTION_11\r\n");
            *outInputKey = INPUT_KEY_ACTION_11;
            break;
        case INPUT_KEY_ACTION_12:
            LOG_INFO("INPUT_KEY_ACTION_12\r\n");
            *outInputKey = INPUT_KEY_ACTION_12;
            break;
        case INPUT_KEY_ACTION_13:
            LOG_INFO("INPUT_KEY_ACTION_13\r\n");
            *outInputKey = INPUT_KEY_ACTION_13;
            break;
        case INPUT_KEY_ACTION_14:
            LOG_INFO("INPUT_KEY_ACTION_14\r\n");
            *outInputKey = INPUT_KEY_ACTION_14;
            break;
        case INPUT_KEY_ACTION_15:
            LOG_INFO("INPUT_KEY_ACTION_15\r\n");
            *outInputKey = INPUT_KEY_ACTION_15;
            break;
        case INPUT_KEY_ACTION_16:
            LOG_INFO("INPUT_KEY_ACTION_16\r\n");
            *outInputKey = INPUT_KEY_ACTION_16;
            break;
        case INPUT_KEY_ACTION_17:
            LOG_INFO("INPUT_KEY_ACTION_17\r\n");
            *outInputKey = INPUT_KEY_ACTION_17;
            break;
        case INPUT_KEY_ACTION_18:
            LOG_INFO("INPUT_KEY_ACTION_18\r\n");
            *outInputKey = INPUT_KEY_ACTION_18;
            break;
        case INPUT_KEY_ACTION_19:
            LOG_INFO("INPUT_KEY_ACTION_19\r\n");
            *outInputKey = INPUT_KEY_ACTION_19;
            break;
        default:
            LOG_INFO("Unknown inpurKey[%d]\r\n", type);
            *outInputKey = INPUT_KEY_NONE;
            break;
    }    
}

void executeFunction(int inpurKey)
{
    switch (inpurKey) {
        case INPUT_KEY_UP:
            LOG_INFO("INPUT_KEY_UP\r\n");
            StraightMove();
            break;
        case INPUT_KEY_DOWN:
            LOG_INFO("INPUT_KEY_DOWN\r\n");
            BackLowMove();
            break;
        case INPUT_KEY_LEFT:
            LOG_INFO("INPUT_KEY_LEFT\r\n");
            LeftTurnMove();
            break;
        case INPUT_KEY_RIGHT:
            LOG_INFO("INPUT_KEY_RIGHT\r\n");
            RightTurnMove();
            break;
        case INPUT_KEY_NONE:
            LOG_INFO("INPUT_KEY_NONE\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_01:
            LOG_INFO("INPUT_KEY_ACTION_01\r\n");
            TargetFindingMove();
            break;
        case INPUT_KEY_ACTION_02:
            LOG_INFO("INPUT_KEY_ACTION_02\r\n");
            GrabWithHand();
            break;
        case INPUT_KEY_ACTION_03:
            LOG_INFO("INPUT_KEY_ACTION_03\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_04:
            LOG_INFO("INPUT_KEY_ACTION_04\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_05:
            LOG_INFO("INPUT_KEY_ACTION_05\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_06:
            LOG_INFO("INPUT_KEY_ACTION_06\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_07:
            LOG_INFO("INPUT_KEY_ACTION_07\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_08:
            LOG_INFO("INPUT_KEY_ACTION_08\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_09:
            LOG_INFO("INPUT_KEY_ACTION_09\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_10:
            LOG_INFO("INPUT_KEY_ACTION_10\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_11:
            LOG_INFO("INPUT_KEY_ACTION_11\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_12:
            LOG_INFO("INPUT_KEY_ACTION_12\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_13:
            LOG_INFO("INPUT_KEY_ACTION_13\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_14:
            LOG_INFO("INPUT_KEY_ACTION_14\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_15:
            LOG_INFO("INPUT_KEY_ACTION_15\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_16:
            LOG_INFO("INPUT_KEY_ACTION_16\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_17:
            LOG_INFO("INPUT_KEY_ACTION_17\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_18:
            LOG_INFO("INPUT_KEY_ACTION_18\r\n");
            StopMove();
            break;
        case INPUT_KEY_ACTION_19:
            LOG_INFO("INPUT_KEY_ACTION_19\r\n");
            StopMove();
            break;
        default:
            LOG_INFO("Unknown inpurKey[%d]\r\n", type);
            StopMove();
            break;
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
    //int isFirst = 0;
    //static int moveCounter = 0;

    while (right <= 250) {
        // 宝物検索用に左右交互に旋回を実行
        //TreasureFindingZigZagMove(&moveCounter);

        //moveCounter++;
        GetAXS1SensorFireData(&left, &center, &right);
        _delay_ms(1);
    }

    // 停止する
    StopMove();
    _delay_ms(500);

	executeRotate(HAND_MOTOR, 60, 560, 560);//つかむ

	executeRotate(WRIST_MOTOR, 60, 250, 250);//持ち上げる

    StraightMove();
    _delay_ms(1000);

    // 停止する
    StopMove();
    _delay_ms(500);

	executeRotate(WRIST_MOTOR, 60, 420, 420);//下す

	executeRotate(HAND_MOTOR, 60, 800, 800);//ひらく

    // 宝物を掴んで荷台に乗せる
    //CatchAndReleaseFormation();

    // ライン上からの旋回を行う
    //executeRightTurnFromOnLine();

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

/***********************************************************************
 * 手の中に搭載している距離センサーをつかって、ターゲットを検索する
 * ロボットアームを左右に動かす⇒少し前進するを繰り返す。
 * 
 ************************************************************************/
void TargetFindingMove(void) {
    const int maxAdjustStraightMoveCount = 100;//カメラ発見後の前進距離最大値を指定
    const int maxMoveWidthCount = 50;//旋回の幅を指定
    const int maxStraightMoveCount = 30;//旋回の幅を指定
    int left = 0, center = 0, right = 0;
    int rihgtMoveCount = 0;
    int leftMoveCount = 0;
    int straightMoveCount = 0;
    int moveVal = 512;

	StopMove();
	_delay_ms(100);

    GetAXS1SensorFireData(&left, &center, &right);
    _delay_ms(1);

    // カメラ発見位置は、手から遠いのである程度直進する
    while (straightMoveCount < maxAdjustStraightMoveCount)
    {
        GetAXS1SensorFireData(&left, &center, &right);
        _delay_ms(1);
        if (right >= 250)
        {
            StopMove();
            _delay_ms(100);
            //閾値を超えたら抜ける
            break;
        }
        StraightMove();
        _delay_ms(5);
        straightMoveCount++;
    }
    straightMoveCount = 0;

    while (right <= 250) {
        // ターゲット検索用に左右交互にアームを動かす
        
        // アームを右へ（右端まで）
        while (rihgtMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (right >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal + rihgtMoveCount;
        	executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);

            rihgtMoveCount++;
        }
        rihgtMoveCount = 0;
    	_delay_ms(100);

        // アームを左へ（中央まで）
        while (leftMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (right >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal - leftMoveCount;
            executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);
            leftMoveCount++;
        }
        leftMoveCount = 0;
    	_delay_ms(100);

        // アームを左へ（左端まで）
        while (leftMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (right >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal - leftMoveCount;
            executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);
            leftMoveCount++;
        }
        leftMoveCount = 0;
    	_delay_ms(100);

        // アームを右へ（中央へ）
        while (rihgtMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (right >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal + rihgtMoveCount;
            executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);

            rihgtMoveCount++;
        }
        rihgtMoveCount = 0;
    	_delay_ms(100);

        GetAXS1SensorFireData(&left, &center, &right);
        _delay_ms(1);
        while (straightMoveCount < maxStraightMoveCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (right >= 250)
            {
                StopMove();
                _delay_ms(100);
                //閾値を超えたら抜ける
                break;
            }
            StraightMove();
            _delay_ms(10);
            straightMoveCount++;
        }
        straightMoveCount = 0;
	    StopMove();
	    _delay_ms(100);

        GetAXS1SensorFireData(&left, &center, &right);
        _delay_ms(1);
    }
    
}

/***********************************************************************
 * 手の中に搭載している距離センサーをつかって、設置台を検索する
 * ロボットアームを左右に動かす⇒少し前進するを繰り返す。
 * 
 ************************************************************************/
void PutTargetOnTable(void)
{
    const int maxAdjustStraightMoveCount = 100;//カメラ発見後の前進距離最大値を指定
    const int maxMoveWidthCount = 50;//旋回の幅を指定
    const int maxStraightMoveCount = 30;//旋回の幅を指定
    int left = 0, center = 0, right = 0;
    int rihgtMoveCount = 0;
    int leftMoveCount = 0;
    int straightMoveCount = 0;
    int moveVal = 512;

    StopMove();
    _delay_ms(100);

    // カメラ発見位置は、手から遠いのである程度直進する
    while (straightMoveCount < maxAdjustStraightMoveCount)
    {
        GetAXS1SensorFireData(&left, &center, &right);
        _delay_ms(1);
        if (right >= 250)
        {
            StopMove();
            _delay_ms(100);
            //閾値を超えたら抜ける
            break;
        }
        StraightMove();
        _delay_ms(5);
        straightMoveCount++;
    }
    straightMoveCount = 0;

    GetAXS1SensorFireData(&left, &center, &right);
    _delay_ms(1);

    while (center <= 250) {
        // ターゲット検索用に左右交互にアームを動かす
            
        // アームを右へ（右端まで）
        while (rihgtMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (center >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal + rihgtMoveCount;
            executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);

            rihgtMoveCount++;
        }
        rihgtMoveCount = 0;
        _delay_ms(100);

        // アームを左へ（中央まで）
        while (leftMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (center >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal - leftMoveCount;
            executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);
            leftMoveCount++;
        }
        leftMoveCount = 0;
        _delay_ms(100);

        // アームを左へ（左端まで）
        while (leftMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (center >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal - leftMoveCount;
            executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);
            leftMoveCount++;
        }
        leftMoveCount = 0;
        _delay_ms(100);

        // アームを右へ（中央へ）
        while (rihgtMoveCount < maxMoveWidthCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (center >= 250)
            {
                //閾値を超えたら抜ける
                break;
            }
            moveVal = moveVal + rihgtMoveCount;
            executeRotate(H_MOV_SHOULDER_MOTOR, 50, moveVal, 10);
            _delay_ms(10);

            rihgtMoveCount++;
        }
        rihgtMoveCount = 0;
        _delay_ms(100);

        GetAXS1SensorFireData(&left, &center, &right);
        _delay_ms(1);
        while (straightMoveCount < maxStraightMoveCount)
        {
            GetAXS1SensorFireData(&left, &center, &right);
            _delay_ms(1);
            if (center >= 250)
            {
                StopMove();
                _delay_ms(100);
                //閾値を超えたら抜ける
                break;
            }
            StraightMove();
            _delay_ms(10);
            straightMoveCount++;
        }
        straightMoveCount = 0;
        StopMove();
        _delay_ms(100);

        GetAXS1SensorFireData(&left, &center, &right);
        _delay_ms(1);
    }
    
}

/**
 * アーム位置の微調整を行う
 * アーム先端が目標物の中央に合うように調整する
 * アームを左右に振って、閾値未満になった角度（もしくはカウント数）を保持。
 * 左右の角度の中央にアームを再セットする。
 *
 */
void FineTuning(void)
{
    
}

/*
 * ロボットを左右交互に旋回して少し前進する。
 * ラインセンサーの値は使用せず、決められた間隔で方向を変える。
 */
void TreasureFindingZigZagMove(int *counter) {
    //const int moveWidthCount = 300;//旋回の幅を指定

    if (m_MoveCounter == 300) {
        if (m_MoveDirerctionFlag == 0) {
            m_MoveDirerctionFlag = 1;
        } else if(m_MoveDirerctionFlag == 1) {
            m_MoveDirerctionFlag = 2;
        } else if(m_MoveDirerctionFlag == 2) {
            m_MoveDirerctionFlag = 3;
        } else if(m_MoveDirerctionFlag == 3) {
            m_MoveDirerctionFlag = 0;
            //        if (m_MoveCounter >= (moveWidthCount * 2)) {
            // counterがmoveWidthCountの２倍になったら
            // 少しだけ前進してリセット
            BaseSpeed = 30;//要調整
            StraightMove();
            _delay_ms(150);//要調整
            m_MoveCounter = 0;
            //        }
        }
        m_MoveCounter=0;
    }

	// counterを判定
	if (m_MoveDirerctionFlag == 0) {
    	// counterがmoveWidthCount以内なら左旋回
    	LeftTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
    	_delay_ms(1);
    } else if (m_MoveDirerctionFlag == 1 || m_MoveDirerctionFlag == 2) {
    	// counterがmoveWidthCount以内なら左旋回
    	RightTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
    	_delay_ms(1);
    } else {
    	// counterがmoveWidthCountより大きい場合右旋回
    	LeftTurnSlowMove(SLOW_TURN_RATE_BY_BASE);
    	_delay_ms(1);
	}
	m_MoveCounter++;
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

//2018年事前審査用動作実行
void execute2018PreExamination(void) {
    LOG_DEBUG("Call execute2018PreExamination() %s\r\n", "");

    //int moveCount = 0;
    //int MAX_COUNT = 500;
    _delay_ms(200);

    FindFormationOnFloor();//アームを検索形態

    // 停止する
    StopMove();
    _delay_ms(300);
    
    // 直進する
    StraightMove();
    _delay_ms(3000);

    // 停止する
    StopMove();
    _delay_ms(300);

    // 左旋回
    LeftTurnMove();
    _delay_ms(3000);
    
    // 停止する
    StopMove();
    _delay_ms(500);

    // 直進する
    StraightMove();
    _delay_ms(3000);

    // 停止する
    StopMove();
    _delay_ms(500);

    // 右旋回
    RightTurnMove();
    _delay_ms(3000);

    // 停止する
    StopMove();
    _delay_ms(500);

    //while (moveCount < MAX_COUNT) {
    //StraightMove();
    //_delay_ms(5);
    //UpBaseSpeed();
    //moveCount++;
    //}

    //treasureHunt_01();

    BackLowMove();//下がる
    _delay_ms(500);

    StopMove();
    _delay_ms(500);

    //SetBaseSpeed(BASE_SPEED_INIT_VAL);// ベーススピードを戻す
    //
    //
    //// 左旋回
    //LeftTurnMove();
    //_delay_ms(2000);
    //
    //StopMove();
    //_delay_ms(500);
    //SetBaseSpeed(BASE_SPEED_INIT_VAL);// ベーススピードを戻す
    //
    //// 直進する
    //while (moveCount < MAX_COUNT) {
    //StraightMove();
    //_delay_ms(10);
    //UpBaseSpeed();
    //moveCount++;
    //}
    //StopMove();
    //_delay_ms(500);
    //SetBaseSpeed(BASE_SPEED_INIT_VAL);// ベーススピードを戻す

    //// 右旋回
    //RightTurnMove();
    //_delay_ms(2000);
    //
    //StopMove();
    //_delay_ms(500);
    //SetBaseSpeed(BASE_SPEED_INIT_VAL);// ベーススピードを戻す
    //
    //// 直進する
    //while (moveCount < MAX_COUNT) {
    //StraightMove();
    //_delay_ms(10);
    //UpBaseSpeed();
    //moveCount++;
    //}
    //StopMove();
    //_delay_ms(500);
    //SetBaseSpeed(BASE_SPEED_INIT_VAL);// ベーススピードを戻す
    //
    StopMove();
}

