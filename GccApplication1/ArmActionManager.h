/*
 * ArmActionManager.h
 *
 * Created: 2017/10/28 22:42:34
 *  Author: Administrator
 */ 


#ifndef ARMACTIONMANAGER_H_
#define ARMACTIONMANAGER_H_

#include <util/delay.h>
#include "include/dynamixel.h"

// ------------------ Defined ------------------
#define HAND_MOTOR              23      // 手先関節のモーター
#define WRIST_MOTOR             14      // 手首関節のモーター
#define ELBOW_MOTOR             25      // 肘関節のモーター
#define H_MOV_SHOULDER_MOTOR    18	    // 水平方向に動く肩関節のモーター


// AX-12A Control Table Address
#define CTRL_TBL_ADDR_PRESENT_POSITION_L	(36)	// Lowest byte of Current Position
#define CTRL_TBL_ADDR_PRESENT_POSITION_H	(37)	// Highest byte of Current Position
#define CTRL_TBL_ADDR_PRESENT_LOAD_L        (40)    // 現在負荷下位ビット
#define CTRL_TBL_ADDR_PRESENT_LOAD_H        (41)    // 現在負荷上位ビット


#define CorrectionValue		    (20) // 補正値
#define JointMoveBaseSpeed		(40) // 

// ------------------ Method Definition ------------------
void initArmMotor(void);


/************************************************************************/
// 床に設置されたターゲット検索用形態
// 手先を床すれすれに変形する。
/************************************************************************/
void FindFormationOnFloor(void);

/************************************************************************/
// 台の上に設置されたターゲット検索用形態
// 手先を床すれすれに変形する。
/************************************************************************/
void FindFormationOnTable(void);

/************************************************************************/
// ターゲット運搬用形態
// ターゲットを床から4cm程度持ち上げた状態に変形する。
/************************************************************************/
void TransportFormation(void);

/************************************************************************/
// 手を閉じる
// 他の関節は動かさない
/************************************************************************/
void GrabWithHand(void);

/************************************************************************/
// 手を開く
// 他の関節は動かさない
/************************************************************************/
void OpenHand(void);

/************************************************************************/
// レバーを下げる用の形態
// 手を高く上げる
/************************************************************************/
void DownLeverFormation(void);

/************************************************************************/
// 収穫エリアで上にぶら下がっているターゲット回収用の形態
// 手を高く上げる
/************************************************************************/
void UpperTargetFormation(void);

/************************************************************************/
// 走行用の形態
// 手首を上げてカメラを前方に向ける
/************************************************************************/
void RunningFormation(void);


void HandUP(void);
void HandDown(void);

void WristUP(void);
void WristDown(void);

void ElbowUP(void);
void ElbowDown(void);

void ShoulderLeft(void);
void ShoulderRight(void);

void CatchAndReleaseFormation(void);

/************************************************************************/
// 現在のモータ角度を表示(Debug用)
// 現在のモータ角度を表示する。
/************************************************************************/
void Debug_AllMotorCurrentAngle(void);

/**
 * 設定角度が目標角度(次ステップへ進んで良い角度) になるまで動作する 
 * @param motorId       モータID
 * @param speed         設定速度
 * @param angle         設定角度
 * @param allowRange    許容角度
 *      次ステップへ進む際の許容範囲。
 *      この値を0に設定するとモータの角度が設定値に達するまで抜けない。
 *      この値を大きくすると、モータの角度が設定値に達しなくても処理を抜けるようになる。
 */
void executeRotate(int motorId, int speed, int angle, int allowRange);

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
int GetCurrentAngle(int motorId);

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
int GetCurrentLoad(int motorId);

#endif /* ARMACTIONMANAGER_H_ */