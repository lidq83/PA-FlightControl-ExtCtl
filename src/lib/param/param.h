/*
 * param.h
 *
 *  Created on: Jul 10, 2018
 *      Author: lidq
 */

#ifndef SRC_LIB_PARAM_PARAM_H_
#define SRC_LIB_PARAM_PARAM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PARAM_NUM			(0x400)
#define PARAM_NAME_SIZE		(0x40)
#define PARAM_SAVE_PATH		"/data/work/workspace/pa/096.PA-FlightControl/rootfs/extctl_params.dat"

typedef enum PARAM_GROUP
{
	PARAM_COMMANDER = 0,
	PARAM_NAVIGATOR,
} param_group_s;

typedef enum PARAM_TYPE
{
	PARAM_INT32 = 0,
	PARAM_UINT32,
	PARAM_FLOAT32
} param_type_s;

typedef struct param_head_s
{
	int param_count;
} param_head_s;

typedef struct param_s
{
	char param_name[PARAM_NAME_SIZE];
	uint8_t param_type;
	uint8_t param_group;
	int param_index;
	int param_count;
	union
	{
		struct
		{
			int32_t i_value;
			int32_t i_default;
		};
		struct
		{
			uint32_t u_value;
			uint32_t u_default;
		};
		struct
		{
			float f_value;
			float f_default;
		};
	};

} param_s;

int param_init(void);

int param_load(void);

int param_save(void);

int param_get(const char *param_name, void *param_value);

int param_set(const char *param_name, void *param_value);

#endif /* SRC_LIB_PARAM_PARAM_H_ */
