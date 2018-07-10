/*
 * nav_block_loiter.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "nav_block_loiter.h"

static ext_vehicle_sp_s _sp = { 0 };

void nav_loiter_on_init(void)
{
}

void nav_loiter_on_desc(void)
{
}

void nav_loiter_on_inactive(void)
{
}

void nav_loiter_on_activation(void)
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	_sp.sp_x = pos->x;
	_sp.sp_y = pos->y;
	_sp.sp_z = pos->z;

	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void nav_loiter_on_active(void)
{
}

bool nav_loiter_is_finished(void)
{
}
