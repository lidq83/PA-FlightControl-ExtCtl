/*
 * extctl_airline.h
 *
 *  Created on: Jun 14, 2018
 *      Author: lidq
 */

#ifndef TESTCODE_EXTCTL_AIRLINE_H_
#define TESTCODE_EXTCTL_AIRLINE_H_

#include "extctl_typedef.h"

#include "extctl_sp.h"
#include "extctl_pos.h"
#include "extctl_rc.h"
#include "extctl_cmd.h"
#include "extctl_status.h"
#include "geo.h"

//accept r
#define ACCEPT_XY		(5.0f)
#define ACCEPT_Z		(2.0f)
//home
#define HOME_LAT		(41.8782246)
#define HOME_LON		(123.4143249)
//FCS MODE
#define MODE_EXTCTL		(13)
//switch mode or armed try times
#define TRY_TIMES		(5)

float dis_z(float sp_z, float pos_z);

float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y);

bool is_reached_xyz(float sp_x, float sp_y, float sp_z, float pos_x, float pos_y, float pos_z);

bool is_reached_xy(float sp_x, float sp_y, float pos_x, float pos_y);

bool is_reached_z(float sp_z, float pos_z);

void wait_reached_xyz(float sp_x, float sp_y, float sp_z);

void wait_reached_xy(float sp_x, float sp_y);

void wait_reached_z(float sp_z);

void airline_test01();

void airline_test02();

#endif /* TESTCODE_EXTCTL_AIRLINE_H_ */
