/*
 * extctl_typedef.h
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_EXTCTL_EXTCTL_TYPEDEF_H_
#define SRC_MODULES_EXTCTL_EXTCTL_TYPEDEF_H_

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <poll.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <semaphore.h>

#define DEV_NAME			"/dev/ttyS2"
#define DEV_BAUDRATE		(B115200)
#define DEV_RATE_BASE		(1000 * 1000)
#define DEV_RATE_READ		(DEV_RATE_BASE / 30)
#define DEV_RATE_POS		(DEV_RATE_BASE / 10)
#define DEV_RATE_RC			(DEV_RATE_BASE / 10)
#define DEV_RATE_SP			(DEV_RATE_BASE / 10)
#define DEV_RATE_STATUS		(DEV_RATE_BASE / 5)

#define FRM_HEAD_0			0X55
#define FRM_HEAD_1			0XAA
#define FRM_FOOT_0			0XA5
#define FRM_FOOT_1			0X5A

#define PAR_HEAD			0
#define PAR_LEN				1
#define PAR_END				2

#define SIZE_BUFF			(0x200)

typedef struct s_buff
{
	int16_t head;
	int16_t tail;
	int16_t size;
	uint8_t buff[SIZE_BUFF];
	uint32_t total_len;
	uint32_t over;
	uint32_t user_buf_over;
} s_buff;

typedef struct vehicle_pos_s
{
	//position local
	struct
	{
		float x;
		float y;
		float z;
	};
	struct
	{
		float vx;
		float vy;
		float vz;
	};
	//position global
	struct
	{
		double lat;
		double lon;
		float alt;
	};
	struct
	{
		float vel_n;
		float vel_e;
		float vel_d;
	};
} vehicle_pos_s;

typedef struct vehicle_sp_s
{
	bool run_pos_control;
	bool run_alt_control;
	bool run_yaw_control;
	float sp_yaw;
	struct
	{
		float sp_x;
		float sp_y;
		float sp_z;
	};
	struct
	{
		float vel_sp_x;
		float vel_sp_y;
		float vel_sp_z;
	};
} vehicle_sp_s;

typedef struct sys_status_s
{
	uint8_t main_state;
	uint8_t nav_state;
	bool armed;
	bool landed;
	bool homed;
	double home_lat;
	double home_lon;
	float home_alt;
} sys_status_s;

typedef struct rc_s
{
	bool rc_failsafe;
	bool rc_lost;
	uint32_t channel_count;
	uint16_t values[18];
} rc_s;

typedef struct cmd_s
{
	uint32_t command;
	float param1;
	float param2;
	float param3;
	float param4;
	float param5;
	float param6;
	float param7;
} cmd_s;

enum data_type
{
	DATA_TYPE_POS = 0,
	DATA_TYPE_SP,
	DATA_TYPE_RC,
	DATA_TYPE_CMD,
	DATA_TYPE_STATUS,
	DATA_TYPE_END,
};

int send_data_buff(void *data, int data_type, int data_len);

#endif /* SRC_MODULES_EXTCTL_EXTCTL_TYPEDEF_H_ */
