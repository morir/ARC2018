/*
 * ArmActionManager.c
 *
 * Created: 2017/10/28 22:38:53
 *  Author: Administrator
 */ 

#include "ArmActionManager.h"

#include "MotorManager.h"
#include "AvrTimer.h"
#include "DebugLog.h"


/************************************************************************/
// Arm用モータの初期設定
// Arm用モータを宝物検索用形態(床ターゲット回収用)の位置に設定
/************************************************************************/
void initArmMotor(void) 
{
	executeRotate(WRIST_MOTOR, 180, 260, 5);
	executeRotate(ELBOW_MOTOR, 100, 350, 10);
	executeRotate(WRIST_MOTOR, 80, 320, 5);
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 1000);
	executeRotate(HAND_MOTOR, 300, 780, 1000);
}

/************************************************************************/
// 床に設置されたターゲット検索用形態
// 手先を床すれすれに変形する。
/************************************************************************/
void FindFormationOnFloor(void)
{
	executeRotate(WRIST_MOTOR, 180, 260, 5);
	executeRotate(ELBOW_MOTOR, 100, 350, 10);
	executeRotate(WRIST_MOTOR, 80, 320, 5);
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 1000);
	executeRotate(HAND_MOTOR, 300, 780, 1000);
}

/************************************************************************/
// 台の上に設置されたターゲット検索用形態
// 手先を床すれすれに変形する。
/************************************************************************/
void FindFormationOnTable(void)
{
	executeRotate(WRIST_MOTOR, 180, 260, 5);
    executeRotate(ELBOW_MOTOR, 50, 460, 10);
    executeRotate(WRIST_MOTOR, 50, 430, 10);
	executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 1000);
	executeRotate(HAND_MOTOR, 400, 780, 1000);
}

/************************************************************************/
// ターゲット運搬用形態
// ターゲットを床から4cm程度持ち上げた状態に変形する。
/************************************************************************/
void TransportFormation(void)
{
    executeRotate(WRIST_MOTOR, 120, 300, 10);
    executeRotate(ELBOW_MOTOR, 100, 535, 100);
    executeRotate(WRIST_MOTOR, 60, 490, 20);
    executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
}

/************************************************************************/
// 手を閉じる
// 他の関節は動かさない
/************************************************************************/
void GrabWithHand(void)
{
	// 手を閉じる
	executeRotate(HAND_MOTOR, 300, 670, 10);
	executeRotate(HAND_MOTOR, 120, 570, 10);
}

/************************************************************************/
// 手を開く
// 他の関節は動かさない
/************************************************************************/
void OpenHand(void)
{
    // 手を開く
    executeRotate(HAND_MOTOR, 40, 600, 10);
    executeRotate(HAND_MOTOR, 120, 650, 10);
    executeRotate(HAND_MOTOR, 250, 780, 1000);
}

/************************************************************************/
// レバーを下げる用の形態
// 手を高く上げる
/************************************************************************/
void DownLeverFormation(void)
{
    executeRotate(WRIST_MOTOR, 120, 300, 10);
    executeRotate(ELBOW_MOTOR, 100, 535, 100);
    executeRotate(WRIST_MOTOR, 60, 490, 20);
    executeRotate(H_MOV_SHOULDER_MOTOR, 50, 512, 10);
}

/************************************************************************/
// 宝物回収＆搭載用形態
// 宝物を回収し、搭載する
// 段階的に動作させ宝物を落とす
/************************************************************************/
void CatchAndReleaseFormation(void)
{
	//-- 掴む
	executeRotate(HAND_MOTOR, 200, 512, 512 );

	//-- 持ち上げ開始	
	executeRotate(ELBOW_MOTOR, 100, 250, 250);
	MotorControlJoint(ELBOW_MOTOR, 100, 680);

	//-- 持ち上げ途中
	executeRotate(ELBOW_MOTOR, 100, 500, 500);

	//-- 落とす直前
	executeRotate(ELBOW_MOTOR, 100, 700, 700);
	MotorControlJoint( ELBOW_MOTOR, 100, 700 );
	_delay_ms(500);//適切なウェイト時間を設定

	//-- 落とす
	executeRotate( WRIST_MOTOR, 200, 620, 620 );
	
	_delay_ms(700);//1秒待つ⇒動作に合わせて変更してください

	//-- 宝物検索用形態に移行するための準備
	MotorControlJoint(ELBOW_MOTOR, 100, 280);
	MotorControlJoint(WRIST_MOTOR, 200, 512);
	MotorControlJoint(ELBOW_MOTOR, 100, 400);	
	executeRotate(ELBOW_MOTOR, 100, 120, 120);
	
	// 宝物検索用ライントレース形態に戻す
	FindFormationOnFloor();
}


/************************************************************************/
// 現在のモータ角度を表示(Debug用)
// 現在のモータ角度を表示する。
/************************************************************************/
void Debug_AllMotorCurrentAngle(void)
{
	LOG_ERROR("GetCurrentAngle(H_MOV_SHOULDER_MOTOR) %d\r\n", GetCurrentAngle(H_MOV_SHOULDER_MOTOR));
	LOG_ERROR("GetCurrentAngle(ELBOW_MOTOR) %d\r\n", GetCurrentAngle(ELBOW_MOTOR));
	LOG_ERROR("GetCurrentAngle(WRIST_MOTOR) %d\r\n", GetCurrentAngle(WRIST_MOTOR));
	LOG_ERROR("GetCurrentAngle(HAND_MOTOR) %d\r\n", GetCurrentAngle(HAND_MOTOR));
}

/**
 * 設定角度が目標角度(次ステップへ進んで良い角度) になるまで動作する 
 * @param motorId       モータID
 * @param speed         設定速度
 * @param angle         設定角度
 * @param allowRange    許容角度(次ステップへ進んで良い角度) 
 */
void executeRotate(int motorId, int speed, int angle, int allowRange){
	//設定角度への動作を実行
	MotorControlJoint( motorId, speed, angle );

	if (allowRange >= 1000) {
        // allowRangeが1000より大きい場合はすぐに処理を抜ける。
        _delay_ms(10);
        return;
    }

    int currentAngle = GetCurrentAngle(motorId);// 現在の角度を更新
    
    LOG_INFO("executeRotate 1 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));

	// 目標角度に達していない間は動作する
    if (currentAngle < angle)
    {
        // 現在角度よりも設定角度が小さい場合
        // 目標角度に達していない間は動作する
        while(1)
        {
            if (currentAngle >= (angle - allowRange))
            {
                LOG_INFO("executeRotate 2-1 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
                break;
            }
    	    _delay_ms(5);//適切なウェイト時間を設定
    	    currentAngle = GetCurrentAngle(motorId);// 現在の角度を更新
            LOG_INFO("executeRotate 2 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
        }
    }
    else
    {
        // 現在角度よりも設定角度が大きい場合
        // 目標角度に達していない間は動作する
        while(1)
        {
            if (currentAngle <= (angle + allowRange))
            {
                LOG_INFO("executeRotate 3-1 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
                break;
            }
    	    _delay_ms(5);//適切なウェイト時間を設定
    	    currentAngle = GetCurrentAngle(motorId);// 現在の角度を更新
            LOG_INFO("executeRotate 3 Low[%d] currentAngle[%d] High[%d]\n", (angle - allowRange), currentAngle, (angle + allowRange));
        }
    }
}

/**
 * 現在のモータ角度取得
 * @brief  現在のモータ角度取得
 * @param  motorId モータID
 * @return 現在の角度
 * @detail 上位バイト2bit、下位8bitから現在の角度を取得する。
 *         パケット通信失敗時、前回の速度を返す。
 *         出力軸：0～300°、0～1023　※中央：150° = 512
 *         300～360°の間：不定値
 *
 *         下記のモータIDを入力パラメータとすること。
 *         H_MOV_SHOULDER_MOTOR 18      // Shoulder Motor address(肩モータ)
 *         ELBOW_MOTOR          25      // Elbow arm Motor address(肘モータ)
 *         WRIST_MOTOR          14      // Wrist Motor address(手首モータ)
 *         HAND_MOTOR           23      // Hand Motor address(手モータ)
 */
int GetCurrentAngle(int motorId) {
	int readValueHigh = 0;	// 上位バイト
	int readValueLow = 0;	// 下位バイト
	static int angle = 0;	// 現在の位置
	
	// 上位バイト取得
	readValueHigh = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_POSITION_H) & 0x03;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// パケット通信失敗時、前回値を返す。
		return angle;
	}
	// 下位バイト取得
	readValueLow  = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_POSITION_L) & 0xFF;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// パケット通信失敗時、前回値を返す。
		return angle;
	}
	// 上位バイトと下位バイトから現在の位置を計算
	angle = ((readValueHigh << 8) + readValueLow);
	LOG_DEBUG("GetCurrentAngle(%d) is %d\n", motorId, angle);
	LOG_INFO("GetCurrentAngle(%d) is %d\n", motorId, angle);

	return angle;
}

/**
 * 現在のモータ負荷取得
 * @brief  現在のモータ負荷取得
 * @param  motorId モータID
 * @return 現在の負荷
 * @detail 上位バイト3bit、下位8bitから現在の負荷を取得する。
 *         出力：0～1023 1023なら100%の負荷状態
 *          上位バイトの4bit目を取得することで負荷方向を取得できるが本関数では未使用とする。
 *
 *         下記のモータIDを入力パラメータとすること。
 *         H_MOV_SHOULDER_MOTOR 18      // Shoulder Motor address(肩モータ)
 *         ELBOW_MOTOR          25      // Elbow arm Motor address(肘モータ)
 *         WRIST_MOTOR          14      // Wrist Motor address(手首モータ)
 *         HAND_MOTOR           23      // Hand Motor address(手モータ)
 */
int GetCurrentLoad(int motorId) {
	int readValueHigh = 0;	// 上位バイト
	int readValueLow = 0;	// 下位バイト
	static int loadVal = 0;	// 現在の負荷
	
	// 上位バイト取得
	readValueHigh = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_LOAD_H) & 0x02;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// パケット通信失敗時、前回値を返す。
		return loadVal;
	}
	// 下位バイト取得
	readValueLow  = dxl_read_byte(motorId, CTRL_TBL_ADDR_PRESENT_LOAD_L) & 0xFF;
	if(dxl_get_result() != COMM_RXSUCCESS) {
		// パケット通信失敗時、前回値を返す。
		return loadVal;
	}
	// 上位バイトと下位バイトから現在の負荷を計算
	loadVal = ((readValueHigh << 8) + readValueLow);
	LOG_DEBUG("GetCurrentAngle(%d) is %d\n", motorId, angle);

	return loadVal;
}
