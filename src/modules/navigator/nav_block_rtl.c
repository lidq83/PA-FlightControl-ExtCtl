/*
 * nav_block_rtl.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "nav_block_rtl.h"

static ext_vehicle_sp_s _sp = { 0 };
static nav_rtl_state_s _state = NAV_RTL_STOP;

static float rtl_climb_alt = -25.0f;
static float rtl_loiter_alt = -15.0f;
static int rtl_loiter_secs = 10;

static hrt_abstime rtl_loiter_time = 0;

static bool rtl_is_reached(void);

static void rtl_reached_sw_state(void);

static void rtl_stop(void);

static void rtl_climb(void);

static void rtl_ret_home(void);

static void rtl_to_loiter(void);

static void rtl_loiter(void);

static void rtl_landing(void);

static void rtl_failsafe(void);

void nav_rtl_on_inactive(void)
{
	rtl_loiter_time = 0;
}

void nav_rtl_on_activation(void)
{
	_state = NAV_RTL_STOP;
	rtl_stop();

}

void nav_rtl_on_active(void)
{
	if (!rtl_is_reached())
	{
		return;
	}

	rtl_reached_sw_state();

	switch (_state)
	{
		case NAV_RTL_STOP:
			rtl_stop();
			break;

		case NAV_RTL_CLIMB:
			rtl_climb();
			break;

		case NAV_RTL_RET_HOME:
			rtl_ret_home();
			break;

		case NAV_RTL_TO_LOITER:
			rtl_to_loiter();
			break;

		case NAV_RTL_LOITER:
			rtl_loiter();
			break;

		case NAV_RTL_LANDING:
			rtl_landing();
			break;

		default:
			rtl_failsafe();
			break;
	}
}

bool rtl_is_reached(void)
{
	bool is_reached = false;

	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	switch (_state)
	{
		case NAV_RTL_STOP:
		{
			if (fabsf(pos->vx) < RTL_REACHED_VEL_XY && fabsf(pos->vy) < RTL_REACHED_VEL_XY && fabsf(pos->vz) < RTL_REACHED_VEL_Z)
			{
				is_reached = true;
			}
			break;
		}
		case NAV_RTL_CLIMB:
		{
			if (nav_block_is_reached_xyz(_sp.sp_x, _sp.sp_y, _sp.sp_z, pos->x, pos->y, pos->z))
			{
				is_reached = true;
			}
			break;
		}

		case NAV_RTL_RET_HOME:
			if (nav_block_is_reached_xyz(_sp.sp_x, _sp.sp_y, _sp.sp_z, pos->x, pos->y, pos->z))
			{
				is_reached = true;
			}
			break;

		case NAV_RTL_TO_LOITER:
		{
			if (nav_block_is_reached_xyz(_sp.sp_x, _sp.sp_y, _sp.sp_z, pos->x, pos->y, pos->z))
			{
				is_reached = true;
			}
			break;
		}

		case NAV_RTL_LOITER:
		{
			long long diff = rtl_loiter_time - hrt_absolute_time();
			if (diff <= 0)
			{
				is_reached = true;
			}
			break;
		}

		case NAV_RTL_LANDING:
		case NAV_RTL_FAILSAFE:
		default:
			break;
	}

	return is_reached;
}

void rtl_reached_sw_state(void)
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	switch (_state)
	{
		case NAV_RTL_STOP:
			if (pos->z > rtl_climb_alt)
			{
				_state = NAV_RTL_CLIMB;
			}
			else
			{
				_state = NAV_RTL_RET_HOME;
			}
			break;

		case NAV_RTL_CLIMB:
			_state = NAV_RTL_RET_HOME;
			break;

		case NAV_RTL_RET_HOME:
			_state = NAV_RTL_TO_LOITER;
			break;

		case NAV_RTL_TO_LOITER:
			_state = NAV_RTL_LOITER;
			break;

		case NAV_RTL_LOITER:
			_state = NAV_RTL_LANDING;
			break;

		case NAV_RTL_LANDING:
		default:
			_state = NAV_RTL_FAILSAFE;
			break;
	}
}

void rtl_stop()
{
	_sp.vel_sp_x = 0.0f;
	_sp.vel_sp_y = 0.0f;
	_sp.vel_sp_z = 0.0f;

	_sp.run_pos_control = false;
	_sp.run_alt_control = false;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void rtl_climb()
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	_sp.sp_x = pos->x;
	_sp.sp_y = pos->y;
	_sp.sp_z = rtl_climb_alt;

	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void rtl_ret_home()
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	_sp.sp_x = 0.0f;
	_sp.sp_y = 0.0f;
	_sp.sp_z = pos->z;

	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void rtl_to_loiter()
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	_sp.sp_x = pos->x;
	_sp.sp_y = pos->y;
	_sp.sp_z = rtl_loiter_alt;

	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void rtl_loiter()
{
	rtl_loiter_time = hrt_absolute_time() + rtl_loiter_secs * 1000 * 1000;

	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	_sp.sp_x = pos->x;
	_sp.sp_y = pos->y;
	_sp.sp_z = rtl_loiter_alt;

	_sp.run_pos_control = true;
	_sp.run_alt_control = true;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void rtl_landing()
{
	ext_vehicle_pos_s *pos = navigator_get_curr_pos();

	_sp.sp_x = pos->x;
	_sp.sp_y = pos->y;

	_sp.vel_sp_z = 0.5f;

	_sp.run_pos_control = true;
	_sp.run_alt_control = false;
	_sp.run_yaw_control = false;

	navigator_set_sp(&_sp);
}

void rtl_failsafe()
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
