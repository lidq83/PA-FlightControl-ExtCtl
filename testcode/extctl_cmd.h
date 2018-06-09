/*
 * extctl_cmd.h
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_EXTCTL_EXTCTL_CMD_H_
#define SRC_MODULES_EXTCTL_EXTCTL_CMD_H_

#include "extctl_typedef.h"

#define VEHICLE_CMD_COMPONENT_ARM_DISARM				(400)
#define VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_ARM		(1)
#define VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_DISARM	(0)

#define VEHICLE_CMD_DO_SET_MODE							(176)
#define VEHICLE_CMD_DO_SET_MODE_CUSTOM_ENABLE			(1)
#define VEHICLE_CMD_DO_SET_MODE_CUSTOM_MAIN_EXTCTL		(10)

int extctl_cmd_handle(void *data);

int extctl_cmd_send(void);

int extctl_cmd_sw_ext_mode(void);

int extctl_cmd_arm(void);

int extctl_cmd_disarm(void);

int extctl_cmd_takeoff(float alt);

int extctl_cmd_falloff(bool altctl, float speed);

int extctl_cmd_setpoint(float x, float y, float z, float yaw);

#endif /* SRC_MODULES_EXTCTL_EXTCTL_CMD_H_ */
