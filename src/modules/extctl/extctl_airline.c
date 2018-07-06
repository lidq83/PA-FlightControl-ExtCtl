/*
 * extctl_airline.c
 *
 *  Created on: Jun 14, 2018
 *      Author: lidq
 */

#include "extctl_airline.h"

extern ext_vehicle_pos_s _pos;
extern ext_sys_status_s _status;

float dis_z(float sp_z, float pos_z)
{
	return (float) sqrt(pow(sp_z - pos_z, 2));
}

float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y)
{
	return (float) sqrt(pow(sp_x - pos_x, 2) + pow(sp_y - pos_y, 2));
}

bool is_reached_xyz(float sp_x, float sp_y, float sp_z, float pos_x, float pos_y, float pos_z)
{
	if (dis_xy(sp_x, sp_y, pos_x, pos_y) < ACCEPT_XY && dis_z(sp_z, pos_z) < ACCEPT_Z)
	{
		return true;
	}

	return false;
}

bool is_reached_xy(float sp_x, float sp_y, float pos_x, float pos_y)
{
	if (dis_xy(sp_x, sp_y, pos_x, pos_y) < ACCEPT_XY)
	{
		return true;
	}

	return false;
}

bool is_reached_z(float sp_z, float pos_z)
{
	if (dis_z(sp_z, pos_z) < ACCEPT_Z)
	{
		return true;
	}

	return false;
}

void wait_reached_xyz(float sp_x, float sp_y, float sp_z)
{
	while (!is_reached_xyz(sp_x, sp_y, sp_z, _pos.x, _pos.y, _pos.z))
	{
		usleep(100 * 1000);
	}
}

void wait_reached_xy(float sp_x, float sp_y)
{
	while (!is_reached_xy(sp_x, sp_y, _pos.x, _pos.y))
	{
		usleep(100 * 1000);
	}
}

void wait_reached_z(float sp_z)
{
	while (!is_reached_z(sp_z, _pos.z))
	{
		usleep(100 * 1000);
	}
}
