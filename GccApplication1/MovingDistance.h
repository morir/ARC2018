/**
 * @file MovingDistance.h
 * @brief �ړ�����
 * @author f.aimano
 * @date 2017/10/28
 */

#ifndef MOVINGDISTANCE_H_
#define MOVINGDISTANCE_H_

typedef enum _MEASUREMENT_STATUS {
	NOT_MEASURING = 0,	// ���v����
	MEASURING,			// �v����
} MEASUREMENT_STATUS;

void StartMeasuringMovingDistance();
void StopMeasuringMovingDistance();
int32_t GetMovingDistance();
void UpdateMovingDistance();

#endif /* MOVINGDISTANCE_H_ */