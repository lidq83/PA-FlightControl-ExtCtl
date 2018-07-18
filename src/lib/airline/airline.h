/*
 * airline.h
 *
 *  Created on: Jul 17, 2018
 *      Author: lidq
 */

#ifndef SRC_LIB_AIRLINE_AIRLINE_H_
#define SRC_LIB_AIRLINE_AIRLINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

#define AIRLINE_PATH_SIZE			(256)
#define AIRLINE_PATH				"/data/work/workspace/pa/PA-FlightControl/rootfs"
#define AIRLINE_MAXNUM				(100)
#define AIRLINE_WAYPOINT_MAXNUM		(10000)

#define WP_ACCEPT_OPT_XY	(1 << 0)
#define WP_ACCEPT_OPT_Z		(1 << 1)
#define WP_ACCEPT_OPT_YAW	(1 << 2)

typedef struct airline_s
{
	int airline_id;
	int waypoint_count;
} airline_s;

typedef struct waypoint_s
{
	bool is_local_sp;
	//local position
	float x;
	float y;
	float z;
	float yaw;
	//global position
	double lat;
	double lon;
	float alt;
	bool is_relative_alt;
	//accept options
	//bit 0: need accept xy, bit 1: need accept z, bit 2: need accept yaw
	//if accept_opt == 0, means just give this point to sp, do not detect if it reached
	int accept_opt;
	float accept_radius_xy;
	float accept_radius_z;
	float accept_yaw;
	//if we reached this waypoint then
	//	if loiter_secs >  0 : loiter n secs
	//	if loiter_secs == 0 : do not loiter
	//	if loiter_secs <  0 : loiter forever
	int loiter_secs;

} waypoint_s;

int airline_init(void);

int airline_save(airline_s *airline, waypoint_s *waypoints);

int airline_load(int airline_id, airline_s *airline, waypoint_s *waypoints);

int airline_get_airline(int airline_id, airline_s *airline);

int airline_get_waypoint(airline_s *airline, int start_index, int count, waypoint_s *waypoints);

void airline_exam01(void);

void airline_exam02(void);

#endif /* SRC_LIB_AIRLINE_AIRLINE_H_ */
