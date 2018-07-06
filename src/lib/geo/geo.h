#ifndef __GEO_H_
#define __GEO_H_

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <math.h>
#include <netinet/in.h>
#include <poll.h>
#include <pthread.h>
#include <semaphore.h>
#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <sys/un.h>

#include <hrt.h>

#define CONSTANTS_ONE_G							9.80665f		/* m/s^2		*/
#define CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C		1.225f			/* kg/m^3		*/
#define CONSTANTS_AIR_GAS_CONST					287.1f 			/* J/(kg * K)		*/
#define CONSTANTS_ABSOLUTE_NULL_CELSIUS			-273.15f		/* °C			*/
#define CONSTANTS_RADIUS_OF_EARTH				6371000			/* meters (m)		*/

#define M_DEG_TO_RAD 							0.01745329251994
#define M_RAD_TO_DEG 							57.2957795130823
#define M_PI_F									3.14159265358979323846f
#define M_TWOPI_F								(M_PI_F * 2.0f)

struct crosstrack_error_s
{
	bool past_end;		// Flag indicating we are past the end of the line/arc segment
	float distance;		// Distance in meters to closest point on line/arc
	float bearing;		// Bearing in radians to closest point on line/arc
};

/* lat/lon are in radians */
struct map_projection_reference_s
{
	uint64_t timestamp;
	double lat_rad;
	double lon_rad;
	double sin_lat;
	double cos_lat;
	bool init_done;
};

struct globallocal_converter_reference_s
{
	float alt;
	bool init_done;
};

int map_projection_init_timestamped(struct map_projection_reference_s *ref, double lat_0, double lon_0, uint64_t timestamp);

int map_projection_init(struct map_projection_reference_s *ref, double lat_0, double lon_0);

/* Transforms a point in the geographic coordinate system to the local
 * azimuthal equidistant plane using the projection given by the argument
 * @param x north
 * @param y east
 * @param lat in degrees (47.1234567°, not 471234567°)
 * @param lon in degrees (8.1234567°, not 81234567°)
 * @return 0 if map_projection_init was called before, -1 else
 */
int map_projection_project(const struct map_projection_reference_s *ref, double lat, double lon, float *x, float *y);

/**
 * Transforms a point in the local azimuthal equidistant plane to the
 * geographic coordinate system using the projection given by the argument
 *
 * @param x north
 * @param y east
 * @param lat in degrees (47.1234567°, not 471234567°)
 * @param lon in degrees (8.1234567°, not 81234567°)
 * @return 0 if map_projection_init was called before, -1 else
 */
int map_projection_reproject(const struct map_projection_reference_s *ref, float x, float y, double *lat, double *lon);

/**
 * Returns the bearing to the next waypoint in radians.
 *
 * @param lat_now current position in degrees (47.1234567°, not 471234567°)
 * @param lon_now current position in degrees (8.1234567°, not 81234567°)
 * @param lat_next next waypoint position in degrees (47.1234567°, not 471234567°)
 * @param lon_next next waypoint position in degrees (8.1234567°, not 81234567°)
 */
float get_bearing_to_next_waypoint(double lat_now, double lon_now, double lat_next, double lon_next);

float _wrap_pi(float bearing);

#endif
