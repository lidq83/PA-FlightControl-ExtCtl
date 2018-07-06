

#pragma once


#include <uORB/uORB.h>




typedef struct vehicle_pos_s
{
	uint64_t timestamp; // required for logger
	double lat;
	double lon;
	float x;
	float y;
	float z;
	float vx;
	float vy;
	float vz;
	float alt;
	float vel_n;
	float vel_e;
	float vel_d;

} vehicle_pos_s;

/* register this as object request broker structure */
ORB_DECLARE(vehicle_pos);

