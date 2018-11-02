/*
 * CFile1.c
 *
 * Created: 2014/07/03 14:01:39
 *  Author: sapporo62
 */ 

#include "SerialManager.h"
#include "DebugLog.h"

volatile int isRead = 0;
volatile int buffCnt = 0;
char readBuffer[SERIAL_BUFFER_SIZE] = {0};

void initSerial(void){
	LOG_INFO( "initSerial\n" );
	serial_initialize(57600);
}

void clearSerialBuffer(){
	LOG_INFO( "clearSerialBuffer\n" );
	isRead = 0;
	memset( &readBuffer[0], 0x00, SERIAL_BUFFER_SIZE );
}

int checkSerialRead(void){
	int ret = 0;
	if( serial_get_qstate() > 0 ){
		unsigned char ReceivedData = getchar();
		if( ReceivedData == 10 || ReceivedData == 13 ){
			if( buffCnt > 0 ){
				buffCnt = 0;
				isRead = 1;
				ret = 1;
			}
		}else if( ReceivedData > 0 ){
			readBuffer[buffCnt++] = ReceivedData;
			if( buffCnt >= SERIAL_BUFFER_SIZE-1 ){
				buffCnt = 0;
				isRead = 1;
				ret = 1;
			}
		}
		LOG_INFO( "readBuffer %s\n", &readBuffer[0] );
	}
	return ret;
}

char * getReadBuffer(){
	LOG_INFO( "getReadBuffer %d\n", isRead );
	char * ret = NULL;
	if( isRead > 0 ){
		LOG_INFO( "readBuffer=%s\n", &readBuffer[0] );
		ret = &readBuffer[0];
		isRead = 0;
	}
	return ret;	
}

void getInputKey(int *outInputKey) {
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
        LOG_INFO("Unknown inpurKey[%d]\r\n", inpurKey);
        *outInputKey = INPUT_KEY_NONE;
        break;
    }
}
