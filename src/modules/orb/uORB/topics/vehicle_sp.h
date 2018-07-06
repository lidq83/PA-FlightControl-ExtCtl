

#pragma once


#include <uORB/uORB.h>




typedef struct vehicle_sp_s
{
	uint64_t timestamp; // required for logger
	float sp_yaw;
	float sp_x;
	float sp_y;
	float sp_z;
	float vel_sp_x;
	float vel_sp_y;
	float vel_sp_z;
	bool run_pos_control;
	bool run_alt_control;
	bool run_yaw_control;
	uint8_t _padding0[1]; // required for logger

} vehicle_sp_s;

/* register this as object request broker structure */
ORB_DECLARE(vehicle_sp);

