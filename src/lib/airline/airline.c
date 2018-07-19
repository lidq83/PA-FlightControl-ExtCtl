/*
 * airline.c
 *
 *  Created on: Jul 17, 2018
 *      Author: lidq
 */

#include <airline.h>
#include <examples.h>

static char _airline_path[AIRLINE_PATH_SIZE] = { 0 };

int airline_init(const char *path)
{
	if (path != NULL)
	{
		strcpy(_airline_path, path);
	}

	if (access(_airline_path, 0) == EOF)
	{
		if (mkdir(_airline_path, 0700))
		{
			printf("[airline] create airline path error.\n");
		}
	}

	char aireline_file[AIRLINE_PATH_SIZE];

	for (int i = 0; i < AIRLINE_MAXNUM; i++)
	{
		snprintf(aireline_file, AIRLINE_PATH_SIZE, "%s/%04d", _airline_path, i);
		if (access(aireline_file, 0) != EOF)
		{
			if (remove(aireline_file))
			{
				printf("[airline] remove file error.\n");
			}
		}
	}

	airline_exam00(0);
	airline_exam01(1);
	airline_exam02(2);
	airline_exam03(3);

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
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", _airline_path, airline->airline_id);

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
		//printf("%d %f %f %f\n", i, waypoints[i].x, waypoints[i].y, waypoints[i].z);
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
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", _airline_path, airline_id);
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
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", _airline_path, airline_id);
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		//printf("[airline] get can not open file %s\n", path);
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
	snprintf(path, AIRLINE_PATH_SIZE, "%s/%04d", _airline_path, airline->airline_id);
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		//printf("[airline] save can not open file %s\n", path);
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
