/*
 * nav_block_reacher.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_REACHED_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_REACHED_H_

#include <lib/geo/geo.h>
#include <navigator.h>

#define ACC_MIN_XY		(1.0)
#define ACC_MIN_Z		(1.0)
#define ACC_MIN_YAW		(1.5 * M_PI / 180.0)

bool nav_block_set_accept_params(float accept_xy, float accept_z, float accept_yaw);

bool nav_block_is_reached_xyz(float sp_x, float sp_y, float sp_z, float pos_x, float pos_y, float pos_z);

bool nav_block_is_reached_xy(float sp_x, float sp_y, float pos_x, float pos_y);

bool nav_block_is_reached_z(float sp_z, float pos_z);

bool nav_block_is_reached_yaw(float sp_yaw, float pos_yaw);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_REACHED_H_ */
