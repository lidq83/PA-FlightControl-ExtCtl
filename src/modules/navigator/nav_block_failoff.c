/*
 * nav_block_failoff.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "nav_block_failoff.h"

static ext_vehicle_sp_s _sp = { 0 };

void nav_failoff_on_init(void)
{
}

void nav_failoff_on_desc(void)
{
}

void nav_failoff_on_inactive(void)
{
}

void nav_failoff_on_activation(void)
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	_sp.sp_yaw = 0.0f;

	_sp.sp_x = pos->x;
	_sp.sp_y = pos->y;
	_sp.sp_z = 0.0f;

	_sp.vel_sp_x = 0.0f;
	_sp.vel_sp_y = 0.0f;
	_sp.vel_sp_z = 0.2f;

	_sp.run_pos_control = true;
	_sp.run_alt_control = false;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void nav_failoff_on_active(void)
{
//	ext_vehicle_pos_s *pos = navigator_get_curr_pos();
//	printf("[pos: %6.3f %6.3f %6.3f][sp: %6.3f %6.3f %6.3f]\n", pos->x, pos->y, pos->z, _sp.sp_x, _sp.sp_y, _sp.sp_z);
}

bool nav_failoff_is_finished(void)
{
}
