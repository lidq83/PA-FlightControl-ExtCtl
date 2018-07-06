/*
 * extctl_typedef.h
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_EXTCTL_EXTCTL_TYPEDEF_H_
#define SRC_MODULES_EXTCTL_EXTCTL_TYPEDEF_H_

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <netinet/in.h>
#include <poll.h>
#include <pthread.h>
#include <semaphore.h>
#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <termios.h>
#include <unistd.h>
#include <orb_manager.h>
#include <uORB/topics/ext_vehicle_pos.h>
#include <uORB/topics/ext_vehicle_sp.h>
#include <uORB/topics/ext_rc.h>
#include <uORB/topics/ext_sys_status.h>
#include <uORB/topics/ext_cmd.h>

#define __USE_SOCKET

#ifdef __USE_SOCKET
#define UNIX_DOMAIN 		"/tmp/UNIX.domain"
#else
#define DEV_NAME			"/dev/ttyUSB0"
#endif

#define DEV_BAUDRATE		(B115200)
#define DEV_RATE_BASE		(1000 * 1000)
#define DEV_RATE_READ		(DEV_RATE_BASE / 30)
#define DEV_RATE_POS		(DEV_RATE_BASE / 10)
#define DEV_RATE_RC			(DEV_RATE_BASE / 10)
#define DEV_RATE_SP			(DEV_RATE_BASE / 10)
#define DEV_RATE_STATUS		(DEV_RATE_BASE / 5)

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
