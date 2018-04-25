/*
 * Extern_control.h
 *
 *  Created on: Apr 21, 2018
 *      Author: lidq
 */

#ifndef SRC_DRIVERS_Extern_CONTROL_EXTERN_CONTROL_H_
#define SRC_DRIVERS_Extern_CONTROL_EXTERN_CONTROL_H_

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

#define DEV_NAME		"/dev/ttyUSB0"
#define DEV_BAUDRATE	(B115200)
#define DEV_RW_RATE		(100)
#define DEV_RW_USLEEP	(1000 * 1000 / DEV_RW_RATE)

#define FRM_HEAD_0		0X55
#define FRM_HEAD_1		0XAA
#define FRM_FOOT_0		0XA5
#define FRM_FOOT_1		0X5A

#define PAR_HEAD		0
#define PAR_LEN			1
#define PAR_END			2

#define SIZE_BUFF		(0x200)

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
	float yaw;
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

enum data_type
{
	DATA_TYPE_POS = 0,
	DATA_TYPE_SP,
	DATA_TYPE_END,
};

int main(int argc, char *argv[]);

static int frame_pos(int len_data);

static int frame_data(char *frame, int len_frame, char *data, int type, int len_data);

static int send_data_pos(vehicle_pos_s *pos);

static int send_data_sp(vehicle_sp_s *sp);

static int send_frame_data(char *frame, int len);

static int start(int argc, char *argv[]);

static int stop(void);

int frame_count(s_buff *lb);

int frame_parse(void);

void frame_read_data(void);

static int task_main_read(int argc, char* argv[]);

static int task_main_write(int argc, char* argv[]);

static uint16_t crc16_value(uint8_t *buff, uint8_t len);

static int crc16_check(uint8_t *buff, uint8_t len, uint16_t crc16);

static int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop);

static int create_points();

#endif /* SRC_DRIVERS_Extern_CONTROL_EXTERN_CONTROL_H_ */
