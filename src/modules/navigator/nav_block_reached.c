/*
 * nav_block_readcher.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include <nav_block_reached.h>

static ext_vehicle_pos_s _pos;

static float dis_z(float sp_z, float pos_z);

static float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y);

float dis_z(float sp_z, float pos_z)
{
	return (float) sqrt(pow(sp_z - pos_z, 2));
}

float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y)
{
	return (float) sqrt(pow(sp_x - pos_x, 2) + pow(sp_y - pos_y, 2));
}

bool nav_block_is_reached_xyz(float sp_x, float sp_y, float sp_z, float pos_x, float pos_y, float pos_z)
{
	if (dis_xy(sp_x, sp_y, pos_x, pos_y) < ACCEPT_XY && dis_z(sp_z, pos_z) < ACCEPT_Z)
	{
		return true;
	}

	return false;
}

bool nav_block_is_reached_xy(float sp_x, float sp_y, float pos_x, float pos_y)
{
	if (dis_xy(sp_x, sp_y, pos_x, pos_y) < ACCEPT_XY)
	{
		return true;
	}

	return false;
}

bool nav_block_is_reached_z(float sp_z, float pos_z)
{
	if (dis_z(sp_z, pos_z) < ACCEPT_Z)
	{
		return true;
	}

	return false;
}

