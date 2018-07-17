/*
 * nav_block_readcher.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include <nav_block_reached.h>

static float _accept_xy = 10;
static float _accept_z = 10;
static float _accept_yaw = 10 * M_PI / 180.0;

static ext_vehicle_pos_s _pos;

static float dis_yaw(float sp_yaw, float pos_yaw);

static float dis_z(float sp_z, float pos_z);

static float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y);

float dis_yaw(float sp_yaw, float pos_yaw)
{
	return (float) sqrt(pow(sp_yaw - pos_yaw, 2));
}

float dis_z(float sp_z, float pos_z)
{
	return (float) sqrt(pow(sp_z - pos_z, 2));
}

float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y)
{
	return (float) sqrt(pow(sp_x - pos_x, 2) + pow(sp_y - pos_y, 2));
}

bool nav_block_set_accept_params(float accept_xy,float accept_z,float accept_yaw)
{
	_accept_xy = accept_xy;
	_accept_z = accept_z;
	_accept_yaw = accept_yaw;
}

bool nav_block_is_reached_xyz(float sp_x, float sp_y, float sp_z, float pos_x, float pos_y, float pos_z)
{
	if (dis_xy(sp_x, sp_y, pos_x, pos_y) <= _accept_xy && dis_z(sp_z, pos_z) < _accept_z)
	{
		return true;
	}

	return false;
}

bool nav_block_is_reached_xy(float sp_x, float sp_y, float pos_x, float pos_y)
{
	if (dis_xy(sp_x, sp_y, pos_x, pos_y) <= _accept_xy)
	{
		return true;
	}

	return false;
}

bool nav_block_is_reached_z(float sp_z, float pos_z)
{
	if (dis_z(sp_z, pos_z) <= _accept_z)
	{
		return true;
	}

	return false;
}

bool nav_block_is_reached_yaw(float sp_yaw, float pos_yaw)
{
	if (dis_yaw(sp_yaw, pos_yaw) <= _accept_yaw)
	{
		return true;
	}

	return false;
}
