/*
 * extctl_cmd.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_cmd.h"

extern vehicle_sp_s _sp;
extern vehicle_pos_s _pos;

static cmd_s _cmd = { 0 };

int extctl_cmd_handle(void *data)
{
	cmd_s *cmd = data;
	if (cmd == NULL)
	{
		return -1;
	}

	return 0;
}

int extctl_cmd_send(void)
{
	return 0;
}

int extctl_cmd_sw_ext_mode(void)
{
	_sp.run_pos_control = false;
	_sp.run_alt_control = false;
	_sp.run_yaw_control = false;

	_sp.sp_x = 0.0f;
	_sp.sp_y = 0.0f;
	_sp.sp_z = 0.0f;

	_sp.vel_sp_x = 0.0f;
	_sp.vel_sp_y = 0.0f;
	_sp.vel_sp_z = 1.0f;

	_sp.sp_yaw = 0.0f;

	_cmd.command = VEHICLE_CMD_DO_SET_MODE;
	_cmd.param1 = VEHICLE_CMD_DO_SET_MODE_CUSTOM_ENABLE;
	_cmd.param2 = VEHICLE_CMD_DO_SET_MODE_CUSTOM_MAIN_EXTCTL;

	extctl_protocal_write(&_cmd, DATA_TYPE_CMD, sizeof(cmd_s));
}

int extctl_cmd_arm(void)
{
	_cmd.command = VEHICLE_CMD_COMPONENT_ARM_DISARM;
	_cmd.param1 = VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_ARM;

	extctl_protocal_write(&_cmd, DATA_TYPE_CMD, sizeof(cmd_s));
}

int extctl_cmd_disarm(void)
{
	_cmd.command = VEHICLE_CMD_COMPONENT_ARM_DISARM;
	_cmd.param1 = VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_DISARM;

	extctl_protocal_write(&_cmd, DATA_TYPE_CMD, sizeof(cmd_s));
}

int extctl_cmd_takeoff(float alt)
{
	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = true;

	_sp.sp_x = 0.0f;
	_sp.sp_y = 0.0f;
	_sp.sp_z = alt;

	_sp.vel_sp_x = 0.0f;
	_sp.vel_sp_y = 0.0f;
	_sp.vel_sp_z = 0.0f;

	_sp.sp_yaw = 0.0f;
}

int extctl_cmd_falloff(float sp_x, float sp_y, float sp_z, float sp_yaw, bool altctl, float speed)
{
	_sp.run_pos_control = true;
	_sp.run_alt_control = altctl;
	_sp.run_yaw_control = true;

	_sp.sp_x = sp_x;
	_sp.sp_y = sp_y;
	_sp.sp_z = sp_z;

	_sp.vel_sp_x = 0.0f;
	_sp.vel_sp_y = 0.0f;
	_sp.vel_sp_z = speed;

	_sp.sp_yaw = sp_yaw;
}

int extctl_cmd_setpoint(float x, float y, float z, float yaw)
{
	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = true;

	_sp.sp_x = x;
	_sp.sp_y = y;
	_sp.sp_z = z;

	_sp.vel_sp_x = 0.0f;
	_sp.vel_sp_y = 0.0f;
	_sp.vel_sp_z = 0.0f;

	_sp.sp_yaw = yaw;
}
