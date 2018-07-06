/*
 * orb_typedef.h
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_UORB_ORB_TYPEDEF_H_
#define SRC_MODULES_UORB_ORB_TYPEDEF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <semaphore.h>

#define ORB_PATH_BASE		"/data/mnt/x"
#define ORB_SIZE_NAME		(0x200)
#define ORB_SUB_MAX_NUM		(0x100)

typedef void* orb_advert_t;

typedef struct s_orb_pub
{
	sem_t sem_rw;
	char sub_updated[ORB_SUB_MAX_NUM];
	void *meta;
} s_orb_pub;

typedef struct s_orb_sub
{
	int fd;
	s_orb_pub *pub;
} s_orb_sub;

#endif /* SRC_MODULES_UORB_ORB_TYPEDEF_H_ */
