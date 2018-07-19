/*
 * examples.c
 *
 *  Created on: Jul 19, 2018
 *      Author: lidq
 */

#include <examples.h>

static float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y);

float dis_xy(float sp_x, float sp_y, float pos_x, float pos_y)
{
	return (float) sqrt(pow(sp_x - pos_x, 2) + pow(sp_y - pos_y, 2));
}

//自由航迹点航线
void airline_exam00(int airline_id)
{
	float alt = -10.0f;
	float yaw = 0.0 * M_PI / 180.0;
	int secs = 2;
	airline_s airline;
	airline.airline_id = airline_id;
	airline.waypoint_count = 6;
	waypoint_s waypoints[airline.waypoint_count];

	memset(waypoints, 0, sizeof(waypoint_s) * airline.waypoint_count);

	int i = 0;
	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].loiter_secs = secs;
	i++;

	waypoints[i].is_local_sp = true;
	waypoints[i].x = 30.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].yaw = yaw;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[i].loiter_secs = secs;
	i++;

	waypoints[i].is_local_sp = true;
	waypoints[i].x = -15;
	waypoints[i].y = -25.9;
	waypoints[i].z = alt;
	waypoints[i].yaw = 0.0;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[i].loiter_secs = secs;
	i++;

	waypoints[i].is_local_sp = true;
	waypoints[i].x = -15;
	waypoints[i].y = 25.9;
	waypoints[i].z = alt;
	waypoints[i].yaw = 0.0;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[i].loiter_secs = secs;
	i++;

	waypoints[i].is_local_sp = true;
	waypoints[i].x = 30.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].yaw = 0.0;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[i].loiter_secs = secs;
	i++;

	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].yaw = 0.0;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[i].loiter_secs = secs;
	i++;

	airline_save(&airline, waypoints);
}

//圆形航点2圈
void airline_exam01(int airline_id)
{
	float alt = -10.0f;
	// 2m/s
	float v = 2.0f;
	// 10hz
	float rate = 10.0f;
	float step = 0.001;
	//loiter secs
	int secs = 3;

	float r = 15.0f;
	int cnt = 0;
	float r_x = 0.0f;
	float r_y = 0.0f;
	for (float angle = M_PI / 2.0; angle < M_PI * 2.0 + M_PI / 2.0; angle += step)
	{
		float x = r * sinf(angle) + r;
		float y = r * cosf(angle);

		if (cnt == 0)
		{
			r_x = x;
			r_y = y;
			cnt++;
			continue;
		}

		if (dis_xy(r_x, r_y, x, y) >= v / rate)
		{
			r_x = x;
			r_y = y;
			cnt++;
		}
	}

	airline_s airline;
	airline.airline_id = airline_id;
	airline.waypoint_count = cnt + 3;
	waypoint_s waypoints[airline.waypoint_count];

	memset(waypoints, 0, sizeof(waypoint_s) * airline.waypoint_count);

	int i = 0;
	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].accept_radius_xy = 1.0;
	waypoints[i].accept_radius_z = 1.0;
	waypoints[i].accept_yaw = 1.5 * M_PI / 180.0;
	waypoints[i].loiter_secs = secs;
	i++;

	waypoints[i].is_local_sp = true;
	waypoints[i].x = r * 2;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].accept_radius_xy = 1.0;
	waypoints[i].accept_radius_z = 1.0;
	waypoints[i].accept_yaw = 1.5 * M_PI / 180.0;
	waypoints[i].loiter_secs = secs;
	i++;

	bool first = true;
	for (float angle = M_PI / 2.0; angle < M_PI * 2.0 + M_PI / 2.0 && i < airline.waypoint_count; angle += step)
	{
		float x = r * sinf(angle) + r;
		float y = r * cosf(angle);

		if (first)
		{
			first = false;

			r_x = x;
			r_y = y;

			waypoints[i].is_local_sp = true;
			waypoints[i].x = r_x;
			waypoints[i].y = r_y;
			waypoints[i].z = alt;
			waypoints[i].accept_opt = 0;
			waypoints[i].loiter_secs = 0;
			i++;
			continue;
		}

		if (dis_xy(r_x, r_y, x, y) >= v / rate)
		{
			r_x = x;
			r_y = y;

			waypoints[i].is_local_sp = true;
			waypoints[i].x = r_x;
			waypoints[i].y = r_y;
			waypoints[i].z = alt;
			waypoints[i].accept_opt = 0;
			waypoints[i].loiter_secs = 0;
			i++;
		}
	}

	waypoints[i].is_local_sp = true;
	waypoints[i].x = r * 2;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].accept_radius_xy = 1.0;
	waypoints[i].accept_radius_z = 1.0;
	waypoints[i].accept_yaw = 1.5 * M_PI / 180.0;
	waypoints[i].loiter_secs = secs;
	i++;

	airline_save(&airline, waypoints);
}

//三叶草2圈
void airline_exam02(int airline_id)
{
	float alt = -10.0f;
	// 2m/s
	float v = 2.0f;
	// 10hz
	float rate = 10.0f;
	float step = 0.001;
	//loiter secs
	int secs = 3;

	float r = 25.0f;
	int cnt = 0;
	float r_x = 0.0f;
	float r_y = 0.0f;
	for (float angle = M_PI / 2.0; angle < M_PI + M_PI / 2.0; angle += step)
	{
		float p = r * cosf(3 * angle);
		float x = p * sinf(angle);
		float y = p * cosf(angle);

		if (cnt == 0)
		{
			r_x = x;
			r_y = y;
			cnt++;
			continue;
		}

		if (dis_xy(r_x, r_y, x, y) >= v / rate)
		{
			r_x = x;
			r_y = y;
			cnt++;
		}
	}

	airline_s airline;
	airline.airline_id = airline_id;
	airline.waypoint_count = cnt + 2;
	waypoint_s waypoints[airline.waypoint_count];

	memset(waypoints, 0, sizeof(waypoint_s) * airline.waypoint_count);

	int i = 0;
	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].loiter_secs = secs;
	i++;

	bool first = true;
	for (float angle = M_PI / 2.0; angle < M_PI + M_PI / 2.0 && i < airline.waypoint_count; angle += step)
	{
		float p = r * cosf(3 * angle);
		float x = p * sinf(angle);
		float y = p * cosf(angle);

		if (first)
		{
			first = false;

			r_x = x;
			r_y = y;

			waypoints[i].is_local_sp = true;
			waypoints[i].x = r_x;
			waypoints[i].y = r_y;
			waypoints[i].z = alt;
			waypoints[i].accept_opt = 0;
			waypoints[i].loiter_secs = 0;
			i++;
			continue;
		}

		if (dis_xy(r_x, r_y, x, y) >= v / rate)
		{
			r_x = x;
			r_y = y;

			waypoints[i].is_local_sp = true;
			waypoints[i].x = r_x;
			waypoints[i].y = r_y;
			waypoints[i].z = alt;
			waypoints[i].accept_opt = 0;
			waypoints[i].loiter_secs = 0;
			i++;
		}
	}

	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].loiter_secs = secs;
	i++;

	airline_save(&airline, waypoints);
}

//阿基米德螺旋线4圈
void airline_exam03(int airline_id)
{
	float alt = -10.0f;
	// 2m/s
	float v = 2.0f;
	// 10hz
	float rate = 10.0f;
	float step = 0.001;
	//loiter secs
	int secs = 3;

	float a = 1.0f;
	float b = 0.5f;
	int cnt = 0;
	float r_x = 0.0f;
	float r_y = 0.0f;
	for (float angle = 0.0; angle < M_PI * 8.0 + M_PI / 2.0; angle += step)
	{
		float r = a + b * angle;
		float x = r * sinf(angle);
		float y = r * cosf(angle);

		if (cnt == 0)
		{
			r_x = x;
			r_y = y;
			cnt++;
			continue;
		}

		if (dis_xy(r_x, r_y, x, y) >= v / rate)
		{
			r_x = x;
			r_y = y;
			cnt++;
		}
	}

	airline_s airline;
	airline.airline_id = airline_id;
	airline.waypoint_count = cnt + 3;
	waypoint_s waypoints[airline.waypoint_count];

	memset(waypoints, 0, sizeof(waypoint_s) * airline.waypoint_count);

	int i = 0;
	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].loiter_secs = secs;
	i++;

	bool first = true;
	for (float angle = 0.0; angle < M_PI * 8.0 + M_PI / 2.0 && i < airline.waypoint_count; angle += step)
	{
		float r = a + b * angle;
		float x = r * sinf(angle);
		float y = r * cosf(angle);

		if (first)
		{
			first = false;

			r_x = x;
			r_y = y;

			waypoints[i].is_local_sp = true;
			waypoints[i].x = r_x;
			waypoints[i].y = r_y;
			waypoints[i].z = alt;
			waypoints[i].accept_opt = 0;
			waypoints[i].loiter_secs = 0;
			i++;
			continue;
		}

		if (dis_xy(r_x, r_y, x, y) >= v / rate)
		{
			r_x = x;
			r_y = y;

			waypoints[i].is_local_sp = true;
			waypoints[i].x = r_x;
			waypoints[i].y = r_y;
			waypoints[i].z = alt;
			waypoints[i].accept_opt = 0;
			waypoints[i].loiter_secs = 0;
			i++;
		}
	}

	waypoints[i].is_local_sp = true;
	waypoints[i].x = r_x;
	waypoints[i].y = r_y;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].loiter_secs = secs;
	i++;

	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = alt;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].loiter_secs = secs;
	i++;

	airline_save(&airline, waypoints);
}
