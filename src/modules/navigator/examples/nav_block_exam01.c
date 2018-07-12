/*
 * nav_block_exam01.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "nav_block_exam01.h"

static ext_vehicle_sp_s _sp = { 0 };
static float _angle = 0.0f;
static float _r = 35.0f;
static float _alt = -10.0f;
static uint8_t _start_by_secs = 10;

static int _mode = 0;

void nav_exam01_on_init(void)
{
	_mode = 0;
}

void nav_exam01_on_desc(void)
{
}

void nav_exam01_on_inactive(void)
{
}

void nav_exam01_on_activation(void)
{
	_mode = 1;

	_angle = M_PI / 2;

	_sp.sp_x = _r * 2.0f;
	_sp.sp_y = 0.0f;
	_sp.sp_z = _alt;

	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void nav_exam01_on_active(void)
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();
	printf("%5.3f %5.3f\n", pos->z, pos->vz);
	if (_mode == 1)
	{
		if (!nav_block_is_reached_xyz(_sp.sp_x, _sp.sp_y, _sp.sp_z, pos->x, pos->y, pos->z))
		{
			return;
		}
		_mode = 2;
	}

	if (_mode == 2)
	{
		if (_angle > M_PI * 6 + M_PI / 2)
		{
			return;
		}

		_angle += 0.01;

		float sp_x = _r * sinf(_angle) + _r;
		float sp_y = _r * cosf(_angle);

		_sp.sp_x = sp_x;
		_sp.sp_y = sp_y;
		_sp.sp_z = _alt;

		_sp.run_pos_control = true;
		_sp.run_alt_control = true;
		_sp.run_yaw_control = false;

		navigator_set_sp(&_sp);

//		int circle = (int) ((_angle - M_PI / 2) / (2 * M_PI));
//		int angle_dis = _angle * 180.0 / M_PI;
//		angle_dis %= 360;
//		printf("[exam01] circle %d angle: %4d\tsp: %+6.2f %+6.2f\n", circle, angle_dis, sp_x, sp_y);
	}
}

bool nav_exam01_is_finished(void)
{
}
