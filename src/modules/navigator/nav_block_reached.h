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

#define ACCEPT_XY		(2.0f)
#define ACCEPT_Z		(1.8f)

bool nav_block_is_reached_xyz(float sp_x, float sp_y, float sp_z, float pos_x, float pos_y, float pos_z);

bool nav_block_is_reached_xy(float sp_x, float sp_y, float pos_x, float pos_y);

bool nav_block_is_reached_z(float sp_z, float pos_z);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_REACHED_H_ */
