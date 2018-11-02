/*
 * SensorManager.h
 *
 * Created: 2014/08/19 18:57:13
 *  Author: Administrator
 */ 

#ifndef SENSORMANAGER_H_
#define SENSORMANAGER_H_

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/common.h>

/* 赤外線センサのポート番号 */
#define     ADC_PORT_1  (1)
#define     ADC_PORT_2  (2)
#define     ADC_PORT_3  (3)
#define     ADC_PORT_4  (4)
#define     ADC_PORT_5  (5)
#define     ADC_PORT_6  (6)

/* 赤外線センサの役割
 * 下記はセンサの配置
 * 進行方向↑　LEFT_OUTSIDE | LEFT_CENTER | LEFT_INSIDE | RIGHT_INSIDE | RIGHT_CENTER | RIGHT_OUTSIDE |
 */
#define LEFT_OUTSIDE	(ADC_PORT_2)	//!< 進行方向 左外側のセンサ
#define LEFT_CENTER		(ADC_PORT_4)	//!< 進行方向 左中央のセンサ
#define LEFT_INSIDE		(ADC_PORT_1)	//!< 進行方向 左内側のセンサ
#define RIGHT_INSIDE	(ADC_PORT_6)	//!< 進行方向 右内側のセンサ
#define RIGHT_CENTER	(ADC_PORT_3)	//!< 進行方向 右中央のセンサ
#define RIGHT_OUTSIDE	(ADC_PORT_5)	//!< 進行方向 右外側のセンサ

//#define COMPARE_VALUE 450//450
#define COMPARE_VALUE 180//450
#define COMPARE_VALUE_RIGHTSIDE 450//450
#define COMPARE_VALUE_LEFTSIDE 450//450
#define COMPARE_VALUE_OTHER 600//ライントレース用の追加した1個のセンサー
#define COMPARE_VALUE_GOAL 700//ゴール判定用のセンサー用

unsigned int values;

int IRArrays[6 + 1];//要素数は (センサ数 + 1)

void timer_init(void);
void initIRSensor(void);
unsigned int ReadIRSensor(unsigned int ch);
void ReadIRSensors(unsigned int * sensors);

int updateIrSensor(int type);
void getIrSensor(void);



#endif /* SENSORMANAGER_H_ */
