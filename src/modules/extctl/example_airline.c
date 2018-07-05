/*
 * example_airline.c
 *
 *  Created on: Jun 26, 2018
 *      Author: lidq
 */

#include "example_airline.h"

extern vehicle_pos_s _pos;
extern sys_status_s _status;

void airline_test01(float airline_alt)
{
	struct map_projection_reference_s _ref_pos;

	for (int i = 1; i <= WAIT_TIME_SEC; i++)
	{
		if (_status.homed)
		{
			map_projection_init(&_ref_pos, _status.home_lat, _status.home_lon);
			break;
		}
		printf("Wait home position vaild %3ds.\n", i);
		sleep(1);
	}
	if (!_status.homed)
	{
		printf("Home position invaild.\n");
		return;
	}
	printf("Set home position %f %f %f.\n", _status.home_lat, _status.home_lon, _status.home_alt);

	//switch ext mode
	for (int i = 0; i < TRY_TIMES && _status.main_state != MODE_EXTCTL; i++)
	{
		extctl_cmd_sw_ext_mode();
		usleep(200 * 1000);
	}
	if (_status.main_state != MODE_EXTCTL)
	{
		printf("Switch Ext Mode Err.\n");
		return;
	}
	printf("Switch Ext Mode.\n");

	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("ExtCtl will start by %2ds.\n", i);
		sleep(1);
	}

	//switch fcs armed
	for (int i = 0; i < TRY_TIMES && !_status.armed; i++)
	{
		extctl_cmd_arm();
		usleep(200 * 1000);
	}
	if (!_status.armed)
	{
		printf("Try to Armed Err.\n");
		return;
	}
	printf("Armed.\n");

	//takeoff begin
	float sp_x = 0.0f;
	float sp_y = 0.0f;
	float sp_z = airline_alt;
	float sp_yaw = 0.0f;

	extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
	printf("Takeoff.\n");
	wait_reached_xyz(sp_x, sp_y, sp_z);

	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("Wait %3d secs.\n", i);
		sleep(1);
	}

	//airline
	float r = 5.0f;
	sp_x = r * 2.0f;
	sp_y = 0.0f;
	sp_z = airline_alt;
	sp_yaw = 0.0f;
	//sp_yaw = - M_PI / 2.0f;
	extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
	printf("Fly to %4.2f %4.2f.\n", sp_x, sp_y);
	wait_reached_xyz(sp_x, sp_y, sp_z);
	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("Wait %3d secs.\n", i);
		sleep(1);
	}

	uint32_t i = 0;
	for (float angle = M_PI / 2; angle < M_PI * 6 + M_PI / 2; angle += 0.03)
	{
		sp_x = r * sinf(angle) + r;
		sp_y = r * cosf(angle);
		//sp_yaw = -angle;
		extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
		if (i++ % 10 == 0)
		{
			int circle = (int) ((angle - M_PI / 2) / (2 * M_PI));
			int angle_dis = angle * 180.0 / M_PI;
			angle_dis %= 360;
			printf("circle %d angle: %4d\tsp: %+6.2f %+6.2f %+6.2f\n", circle, angle_dis, sp_x, sp_y, sp_z);
		}
		usleep(100 * 1000);
	}

	//return to home
	sp_x = 0.0f;
	sp_y = 0.0f;
	sp_z = airline_alt;
	sp_yaw = 0.0f;
//	double lat = HOME_LAT;
//	double lon = HOME_LON;
//	map_projection_reproject(&_ref_pos, 0.0f, 0.0f, &lat, &lon);
//	sp_yaw = get_bearing_to_next_waypoint(_pos.lat, _pos.lon, lat, lon);

	extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
	printf("Return to home.\n", sp_y, sp_z, sp_z, sp_yaw);
	wait_reached_xyz(sp_x, sp_y, sp_z);

	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("Wait %3d secs.\n", i);
		sleep(1);
	}

	//landing
	sp_x = 0.0f;
	sp_y = 0.0f;
	sp_z = 0.0f;
	sp_yaw = 0.0f;
	printf("Landing\n");
	while (1)
	{
		float z = _pos.z;
		if (z < -5.0f)
		{
			extctl_cmd_falloff(sp_x, sp_y, sp_z, sp_yaw, true, 0.0f);
		}
		else
		{
			extctl_cmd_falloff(sp_x, sp_y, sp_z, sp_yaw, false, 0.2f);
		}
		if (_pos.z >= 0)
		{
			break;
		}
		usleep(100 * 1000);
	}
	printf("Landed.\n");

	for (int i = 0; i < _status.armed; i++)
	{
		extctl_cmd_disarm();
		usleep(200 * 1000);
	}
}

void airline_test02(float airline_alt)
{
	struct map_projection_reference_s _ref_pos;

	for (int i = 1; i <= WAIT_TIME_SEC; i++)
	{
		if (_status.homed)
		{
			map_projection_init(&_ref_pos, _status.home_lat, _status.home_lon);
			break;
		}
		printf("Wait home position vaild %3ds.\n", i);
		sleep(1);
	}
	if (!_status.homed)
	{
		printf("Home position invaild.\n");
		return;
	}
	printf("Set home position %f %f %f.\n", _status.home_lat, _status.home_lon, _status.home_alt);

	//switch ext mode
	for (int i = 0; i < TRY_TIMES && _status.main_state != MODE_EXTCTL; i++)
	{
		extctl_cmd_sw_ext_mode();
		usleep(200 * 1000);
	}
	if (_status.main_state != MODE_EXTCTL)
	{
		printf("Switch Ext Mode Err.\n");
		return;
	}
	printf("Switch Ext Mode.\n");

	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("ExtCtl will start by %2ds.\n", i);
		sleep(1);
	}

	//switch fcs armed
	for (int i = 0; i < TRY_TIMES && !_status.armed; i++)
	{
		extctl_cmd_arm();
		usleep(200 * 1000);
	}
	if (!_status.armed)
	{
		printf("Try to Armed Err.\n");
		return;
	}
	printf("Armed.\n");

	//takeoff begin
	float sp_x = 0.0f;
	float sp_y = 0.0f;
	float sp_z = airline_alt;
	float sp_yaw = 0.0f;

	extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
	printf("Takeoff.\n");
	wait_reached_xyz(sp_x, sp_y, sp_z);

	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("Wait %3d secs.\n", i);
		sleep(1);
	}

	//airline
	float a = 15.0f;
	sp_x = 0.0f;
	sp_y = 0.0f;
	sp_z = airline_alt;
	sp_yaw = 0.0f;
	//sp_yaw = - M_PI / 2.0f;
	extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
	printf("Fly to %4.2f %4.2f.\n", sp_x, sp_y);
	wait_reached_xyz(sp_x, sp_y, sp_z);
	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("Wait %3d secs.\n", i);
		sleep(1);
	}

	uint32_t i = 0;
	for (float angle = M_PI / 2; angle < M_PI * 4 + M_PI / 2; angle += 0.003)
	{
		float p = a * cosf(3 * angle);
		sp_x = p * sinf(angle);
		sp_y = p * cosf(angle);
		//sp_yaw = -angle;
		extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
		if (i++ % 10 == 0)
		{
			int circle = (int) ((angle - M_PI / 2) / (2 * M_PI));
			int angle_dis = angle * 180.0 / M_PI;
			angle_dis %= 360;
			printf("circle %d angle: %d\tsp: %+6.2f %+6.2f %+6.2f\n", circle, angle_dis, sp_x, sp_y, sp_z);
		}
		usleep(100 * 1000);
	}

	//return to home
	sp_x = 0.0f;
	sp_y = 0.0f;
	sp_z = airline_alt;
	sp_yaw = 0.0f;
//	double lat = HOME_LAT;
//	double lon = HOME_LON;
//	map_projection_reproject(&_ref_pos, 0.0f, 0.0f, &lat, &lon);
//	sp_yaw = get_bearing_to_next_waypoint(_pos.lat, _pos.lon, lat, lon);

	extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
	printf("Return to home.\n", sp_y, sp_z, sp_z, sp_yaw);
	wait_reached_xyz(sp_x, sp_y, sp_z);

	for (int i = WAIT_TIME_SEC; i > 0; i--)
	{
		printf("Wait %3d secs.\n", i);
		sleep(1);
	}

	//landing
	sp_x = 0.0f;
	sp_y = 0.0f;
	sp_z = 0.0f;
	sp_yaw = 0.0f;
	printf("Landing\n");
	while (1)
	{
		float z = _pos.z;
		if (z < -5.0f)
		{
			extctl_cmd_falloff(sp_x, sp_y, sp_z, sp_yaw, true, 0.0f);
		}
		else
		{
			extctl_cmd_falloff(sp_x, sp_y, sp_z, sp_yaw, false, 0.2f);
		}

		if (_pos.z >= 0)
		{
			break;
		}
		usleep(100 * 1000);
	}

	printf("Landed.\n");

	for (int i = 0; i < _status.armed; i++)
	{
		extctl_cmd_disarm();
		usleep(200 * 1000);
	}
}

//void airline_test03(float airline_alt)
//{
//	struct map_projection_reference_s _ref_pos;
//
//	for (int i = 1; i <= 60; i++)
//	{
//		if (_status.homed)
//		{
//			map_projection_init(&_ref_pos, _status.home_lat, _status.home_lon);
//			break;
//		}
//		printf("Wait home position vaild %3ds.\n", i);
//		usleep(10 * 1000);
//	}
//	if (!_status.homed)
//	{
//		printf("Home position invaild.\n");
//		return;
//	}
//	printf("Set home position %f %f %f.\n", _status.home_lat, _status.home_lon, _status.home_alt);
//
//	//switch ext mode
//	for (int i = 0; i < TRY_TIMES && _status.main_state != MODE_EXTCTL; i++)
//	{
//
//		extctl_cmd_sw_ext_mode();
//		usleep(100 * 1000);
//	}
//	if (_status.main_state != MODE_EXTCTL)
//	{
//		printf("Switch Ext Mode Err.\n");
//		return;
//	}
//	printf("Switch Ext Mode.\n");
//	usleep(10 * 1000);
//
//	//switch fcs armed
//	for (int i = 0; i < TRY_TIMES && !_status.armed; i++)
//	{
//		extctl_cmd_arm();
//		usleep(10 * 1000);
//	}
//	if (!_status.armed)
//	{
//		printf("Try to Armed Err.\n");
//		return;
//	}
//	printf("Armed.\n");
//
//	//airline
//	float sp_x = 0.0f;
//	float sp_y = 0.0f;
//	float sp_z = airline_alt;
//	float sp_yaw = 0.0f;
//
//	extctl_cmd_setpoint(sp_x, sp_y, sp_z, sp_yaw);
//	printf("Fly to %4.2f %4.2f.\n", sp_x, sp_y);
//
//	usleep(100 * 1000);
//}

