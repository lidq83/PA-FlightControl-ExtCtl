/*
 * airline.c
 *
 *  Created on: Jul 17, 2018
 *      Author: lidq
 */

#include <airline.h>

int airline_init(void)
{
	printf("way size %d\n", sizeof(waypoint_s));
	//airline_exam01();
	airline_exam02();

	return 0;
}

int airline_save(airline_s *airline, waypoint_s *waypoints)
{
	if (airline == NULL)
	{
		printf("[airline] save airline is NULL\n");
		return -1;
	}

	if (waypoints == NULL)
	{
		printf("[airline] save waypoints is NULL\n");
		return -1;
	}

	if (airline->waypoint_count <= 0 || airline->waypoint_count > AIRLINE_WAYPOINT_MAXNUM)
	{
		printf("[airline] load waypoint_count error\n");
		return -1;
	}

	char path[AIRLINE_PATH_SIZE];
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", AIRLINE_PATH, airline->airline_id);
	FILE *fp = fopen(path, "w+");
	if (fp == NULL)
	{
		printf("[airline] save can not open file %s\n", path);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	int len = fwrite(airline, sizeof(airline_s), 1, fp);
	if (len != 1)
	{
		printf("[airline] save can not write file %s\n", path);
		goto _out;
	}

	for (int i = 0; i < airline->waypoint_count; i++)
	{
		len = fwrite(&waypoints[i], sizeof(waypoint_s), 1, fp);
		//printf("%f %f %f\n", waypoints[i].x, waypoints[i].y, waypoints[i].z);
		if (len != 1)
		{
			printf("[airline] save write file error %s\n", path);
			goto _out;
		}
	}
	printf("[airline] save ok\n");
	fclose(fp);
	return 0;

	_out: ;
	fclose(fp);
	return -1;
}

int airline_load(int airline_id, airline_s *airline, waypoint_s *waypoints)
{
	if (airline == NULL)
	{
		printf("[airline] load airline is NULL\n");
		return -1;
	}

	if (waypoints == NULL)
	{
		printf("[airline] load waypoints is NULL\n");
		return -1;
	}

	char path[AIRLINE_PATH_SIZE];
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", AIRLINE_PATH, airline_id);
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("[airline] load can not open file %s\n", path);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	int len = fread(airline, sizeof(airline_s), 1, fp);
	if (len != 1)
	{
		printf("[airline] load can not read file %s\n", path);
		goto _out;
	}

	if (airline->waypoint_count <= 0 || airline->waypoint_count > AIRLINE_WAYPOINT_MAXNUM)
	{
		printf("[airline] load waypoint_count error %s\n", path);
		goto _out;
	}
	for (int i = 0; i < airline->waypoint_count; i++)
	{
		len = fread(waypoints + sizeof(waypoint_s) * i, sizeof(waypoint_s), 1, fp);
		if (len != 1)
		{
			printf("[airline] load read file error %s\n", path);
			goto _out;
		}
	}

	fclose(fp);
	return 0;

	_out: ;
	fclose(fp);
	return -1;
}

int airline_get_airline(int airline_id, airline_s *airline)
{
	if (airline == NULL)
	{
		printf("[airline] get airline is NULL\n");
		return -1;
	}

	char path[AIRLINE_PATH_SIZE];
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", AIRLINE_PATH, airline_id);
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("[airline] get can not open file %s\n", path);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	int len = fread(airline, sizeof(airline_s), 1, fp);
	if (len != 1)
	{
		printf("[airline] get can not read file %s\n", path);
		goto _out;
	}

	fclose(fp);
	return 0;

	_out: ;
	fclose(fp);
	return -1;
}

int airline_get_waypoint(airline_s *airline, int start_index, int count, waypoint_s *waypoints)
{
	if (airline == NULL)
	{
		printf("[airline] get waypoints is NULL\n");
		return -1;
	}

	if (waypoints == NULL)
	{
		printf("[airline] get waypoints is NULL\n");
		return -1;
	}

	if (start_index < 0)
	{
		printf("[airline] get waypoints index < 0\n");
		return -1;
	}

	char path[AIRLINE_PATH_SIZE];
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", AIRLINE_PATH, airline->airline_id);
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("[airline] save can not open file %s\n", path);
		return -1;
	}

	if (start_index + count > airline->waypoint_count)
	{
		count = airline->waypoint_count - start_index;
	}

	fseek(fp, 0, SEEK_SET);

	int len = fread(airline, sizeof(airline_s), 1, fp);
	if (len != 1)
	{
		printf("[airline] get can not read file %s\n", path);
		goto _out;
	}

	fseek(fp, sizeof(airline_s) + sizeof(waypoint_s) * start_index, SEEK_SET);

	for (int i = 0; i < count; i++)
	{
		len = fread(&waypoints[i], sizeof(waypoint_s), 1, fp);
		//printf("%f %f %f\n", waypoints[i].x, waypoints[i].y, waypoints[i].z);
		if (len != 1)
		{
			printf("[airline] load read file error %s\n", path);
			goto _out;
		}
	}

	fclose(fp);
	return count;

	_out: ;
	fclose(fp);
	return -1;
}

void airline_exam01(void)
{
	printf("[airline] exam01\n");

	airline_s airline;
	airline.airline_id = 0;
	airline.waypoint_count = 4;
	waypoint_s waypoints[airline.waypoint_count];

	memset(&waypoints[0], 0, sizeof(waypoint_s) * airline.waypoint_count);

	waypoints[0].is_local_sp = true;
	waypoints[0].x = 0.0;
	waypoints[0].y = 0.0;
	waypoints[0].z = -10.0;
	waypoints[0].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[0].accept_radius_xy = 1.0;
	waypoints[0].accept_radius_z = 1.0;
	waypoints[0].loiter_secs = 10;

	waypoints[1].is_local_sp = true;
	waypoints[1].x = 30.0;
	waypoints[1].y = 30.0;
	waypoints[1].z = -30.0;
	waypoints[1].yaw = M_PI / 3.0;
	waypoints[1].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[1].accept_radius_xy = 1.0;
	waypoints[1].accept_radius_z = 1.0;
	waypoints[1].accept_yaw = 1.5 * M_PI / 180.0;
	waypoints[1].loiter_secs = 10;

	waypoints[2].is_local_sp = true;
	waypoints[2].x = 0.0;
	waypoints[2].y = 0.0;
	waypoints[2].z = -30.0;
	waypoints[2].yaw = 0.0;
	waypoints[2].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[2].accept_radius_xy = 1.0;
	waypoints[2].accept_radius_z = 1.0;
	waypoints[2].accept_yaw = 1.5 * M_PI / 180.0;
	waypoints[2].loiter_secs = 10;

	waypoints[3].is_local_sp = true;
	waypoints[3].x = 0.0;
	waypoints[3].y = 0.0;
	waypoints[3].z = -10.0;
	waypoints[3].yaw = 0.0;
	waypoints[3].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z | WP_ACCEPT_OPT_YAW;
	waypoints[3].accept_radius_xy = 1.0;
	waypoints[3].accept_radius_z = 1.0;
	waypoints[3].accept_yaw = 1.5 * M_PI / 180.0;
	waypoints[3].loiter_secs = 10;

	airline_save(&airline, waypoints);
}

void airline_exam02(void)
{
	printf("[airline] exam02\n");

	float r = 10.0f;
	int cnt = 0;
	for (float angle = M_PI / 2.0; angle < M_PI * 4 + M_PI / 2.0; angle += 0.01)
	{
		cnt++;
	}

	airline_s airline;
	airline.airline_id = 0;
	airline.waypoint_count = cnt + 2;
	waypoint_s waypoints[airline.waypoint_count];

	printf("[nav] exam02 %d\n", cnt);

	memset(&waypoints[0], 0, sizeof(waypoint_s) * airline.waypoint_count);

	int i = 0;
	waypoints[i].is_local_sp = true;
	waypoints[i].x = r * 2;
	waypoints[i].y = 0.0;
	waypoints[i].z = -10.0;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].accept_radius_xy = 1.0;
	waypoints[i].accept_radius_z = 1.0;
	waypoints[i].loiter_secs = 10;
	i++;

	for (float angle = M_PI / 2.0; angle < M_PI * 4 + M_PI / 2.0 && i < airline.waypoint_count; angle += 0.01, i++)
	{
		float x = r * sinf(angle) + r;
		float y = r * cosf(angle);

		waypoints[i].is_local_sp = true;
		waypoints[i].x = x;
		waypoints[i].y = y;
		waypoints[i].z = -10.0;
		waypoints[i].accept_opt = 0;
		waypoints[i].loiter_secs = 0;
	}

	waypoints[i].is_local_sp = true;
	waypoints[i].x = 0.0;
	waypoints[i].y = 0.0;
	waypoints[i].z = -10.0;
	waypoints[i].accept_opt = WP_ACCEPT_OPT_XY | WP_ACCEPT_OPT_Z;
	waypoints[i].accept_radius_xy = 1.0;
	waypoints[i].accept_radius_z = 1.0;
	waypoints[i].loiter_secs = -1;
	i++;

	airline_save(&airline, waypoints);
}
