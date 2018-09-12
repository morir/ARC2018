/*
 * MotorManager.h
 *
 * Created: 2014/10/29 14:46:58
 *  Author: Administrator
 */

#ifndef MOTOR_MANAGER_H_
#define MOTOR_MANAGER_H_
 
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include "include/dynamixel.h"
#include "AvrTimer.h"

// ------------------ Defined ------------------
#define DEFAULT_BAUDNUM     1 // 1Mbps

#define RIGHT_MOTOR         32      // Right Motor address
#define LEFT_MOTOR          33      // Left Motor address
#define CENTER_AXS1_SENSOR	100		// AX-S1 Sensor address

// Motor Settings Address
#define P_CW_ANGLE_LIMIT_L  6
#define P_CW_ANGLE_LIMIT_H  7
#define P_CCW_ANGLE_LIMIT_L 8
#define P_CCW_ANGLE_LIMIT_H 9
#define P_GOAL_POSITION_L   30
#define P_GOAL_POSITION_H   31
#define P_GOAL_SPEED_L      32
#define P_GOAL_SPEED_H      33
#define P_EEP_LOCK          47

#define CARGO_BED_MOTOR	     18		 // 荷台用モータのID

// MX-12W Control Table Address
#define CTRL_TBL_ADDR_PRESENT_SPEED_L	(38)	// Lowest byte of Current Speed 
#define CTRL_TBL_ADDR_PRESENT_SPEED_H	(39)	// Highest byte of Current Speed

// AX-S1  Control Table Address
#define AXS1_ADDR_IR_LEFT_FIRE_DATA		(26)	// 左側の赤外線センサ値
#define AXS1_ADDR_IR_CENTER_FIRE_DATA	(27)	// 中央の赤外線センサ値
#define AXS1_ADDR_IR_RIGHT_FIRE_DATA	(28)	// 右側の赤外線センサ値
#define AXS1_ADDR_IR_LIGHT_LEFT_DATA	(29)	// 左側の照度センサ値
#define AXS1_ADDR_IR_LIGHT_CENTER_DATA	(30)	// 中央の照度センサ値
#define AXS1_ADDR_IR_LIGHT_RIGHT_DATA	(31)	// 右側の照度センサ値

// Speed settings
#define MAX_SPEED (130)

// Trace pattern
#define TRACE_UNDEFINED			(-1)// 未定義(前回の動作を継続)
#define TRACE_STRAIGHT			0	// 直進
#define TRACE_L_STRAIGHT		1	// 左前進
#define TRACE_L_ROUND_SOFT		7	// 左カーブ(Soft)
#define TRACE_L_ROUND_MIDDLE	2	// 左カーブ(Middle)
#define TRACE_L_ROUND_TIGHT		8	// 左カーブ(Tight)
#define TRACE_L_TURN_START		111	// 左旋回開始
#define TRACE_L_TURN			5	// 左旋回
#define TRACE_L_TURN_END		112	// 左旋回終了
#define TRACE_R_STRAIGHT		3	// 右前進
#define TRACE_R_ROUND_SOFT		9	// 右カーブ(Soft)
#define TRACE_R_ROUND_MIDDLE	4	// 右カーブ(Middle)
#define TRACE_R_ROUND_TIGHT		10	// 右カーブ(Tight)
#define TRACE_R_TURN_START		113	// 右旋回開始
#define TRACE_R_TURN			6	// 右旋回
#define TRACE_R_TURN_END		114	// 右旋回終了
#define TRACE_SLOW_STRAIGHT		12	// 直進
#define TRACE_L_TRESURE_FIND    115	// 宝物検索左前進
#define TRACE_R_TRESURE_FIND    116	// 宝物検索右前進
#define TRACE_FINALACTION		999	// ゴール動作

#define MOTOR_MOVE_UP_VAL		(20)	//モーターが低速だった場合この値分を付加して駆動させる
#define TURN_SPEED_BASE			(50)	//旋回のベース速度
#define BASE_SPEED_INIT_VAL		(80)	//ベース速度の初期値
#define TURN_SPEED_JUDGE_VAL	(400)	//定常旋回する基準速度
#define TRESURE_FIND_INSIDEMORTER_MOVE_VAL	(20)	//内側のモータ速度を1～100を％で指定。100で直進、1で内側モータほぼ停止。
#define BASE_SPEED_BY_TURF_AREA (50)    //芝エリア用のベース速度
#define BASE_SPEED_BY_SLOWMOVE (90)    //芝エリア前のセクションのMAXベース速度

#define MOTOR_MOVE_UP_VAL	(20)	//モーターが低速だった場合この値分を付加して駆動させる
#define SLOW_STRAIGHT_VAL	(120)	//旋回位置微調整で動作する速度(前進用)
#define SLOW_BACK_VAL	(100)	//旋回位置微調整で動作する速度(後進用)

// ------------------ Method Definition ------------------
void MotorInit(void);
void MotorControl(int id, int power);
void MotorControlJoint(int id, int speed, int position);
void Execute(int type);
void StopMove(void);
void StraightMove(void);
void StraightLowMove(void);
void StraightLowMove2(void);
void BackLowMove(void);
void Move(int leftSpeed, int rightSpeed);
void LeftStraightMove(void);
void RightStraightMove(void);
void LeftSoftRoundMove(void);
void LeftMiddleRoundMove(void);
void LeftTightRoundMove(void);
void RightSoftRoundMove(void);
void RightMiddleRoundMove(void);
void RightTightRoundMove(void);
void LeftTurnMove(void);
void RightTurnMove(void);
void LeftTurnSlowMove(int rate);
void RightTurnSlowMove(int rate);
void PrintErrorCode(void);
void PrintCommStatus(int CommStatus);
void LeftTresureFindMove(void);
void RightTresureFindMove(void);
void stopMoveLessThanVal(int val);

int GetCurrentSpeedR(void);
int GetCurrentSpeedL(void);
int GetCurrentSignedSpeedR(void);
int GetCurrentSignedSpeedL(void);
int GetCurrentAngle(int motorId);

void GetAXS1SensorFireData(int *out_fire_data_left, int *out_fire_data_center, int *out_fire_data_right);

int mCount;
int BaseSpeed;

#endif // MOTOR_MANAGER_H_