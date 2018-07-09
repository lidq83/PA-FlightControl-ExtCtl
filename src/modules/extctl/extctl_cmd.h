/*
 * extctl_cmd.h
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_EXTCTL_EXTCTL_CMD_H_
#define SRC_MODULES_EXTCTL_EXTCTL_CMD_H_

#include "extctl_protocol.h"
#include "extctl_typedef.h"

int extctl_cmd_init(void);

int extctl_cmd_handle(void *data);

int extctl_cmd_send(void);

//int extctl_cmd_sw_ext_mode(void);
//
//int extctl_cmd_arm(void);
//
//int extctl_cmd_disarm(void);
//
//int extctl_cmd_takeoff(float alt);
//
//int extctl_cmd_falloff(float sp_x, float sp_y, float sp_z, float sp_yaw, bool altctl, float speed);
//
//int extctl_cmd_setpoint(float x, float y, float z, float yaw);

#endif /* SRC_MODULES_EXTCTL_EXTCTL_CMD_H_ */
