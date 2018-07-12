/*
 * nav_block_mission.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "nav_block_mission.h"

static ext_vehicle_sp_s _sp = { 0 };

void nav_mission_on_init(void)
{
}

void nav_mission_on_desc(void)
{
}

void nav_mission_on_inactive(void)
{

}

void nav_mission_on_activation(void)
{
	_sp.sp_yaw = M_PI / 4.0;

	_sp.sp_x = 30.0f;
	_sp.sp_y = 30.0f;
	_sp.sp_z = -40.0f;

	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = true;

	navigator_set_sp(&_sp);
}

void nav_mission_on_active(void)
{

}

bool nav_mission_is_finished(void)
{
}
