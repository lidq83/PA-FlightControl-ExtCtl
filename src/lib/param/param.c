/*
 * param.c
 *
 *  Created on: Jul 10, 2018
 *      Author: lidq
 */

#include <param.h>

static param_head_s _param_head;

static param_s *_params = NULL;

int param_init(void)
{
	if (_params == NULL)
	{
		_params = malloc(sizeof(param_s) * PARAM_NUM);
		if (_params == NULL)
		{
			printf("[params] malloc error.\n");
			return -1;
		}
		printf("[params] malloc size %d.\n", sizeof(param_s) * PARAM_NUM);
	}

	int ind = 0;

	//返航爬升高度
	strncpy(_params[ind].param_name, "NAV_RTL_CLIMB_ALT", PARAM_NAME_SIZE);
	_params[ind].param_type = PARAM_FLOAT32;
	_params[ind].param_group = PARAM_NAVIGATOR;
	_params[ind].f_default = -50.0;
	_params[ind].f_value = -50.0;
	ind++;

	//返航盘旋高度
	strncpy(_params[ind].param_name, "NAV_RTL_LOITER_ALT", PARAM_NAME_SIZE);
	_params[ind].param_type = PARAM_FLOAT32;
	_params[ind].param_group = PARAM_NAVIGATOR;
	_params[ind].f_default = -40.0;
	_params[ind].f_value = -40.0;
	ind++;

	//返航盘旋时间
	strncpy(_params[ind].param_name, "NAV_RTL_LOITER_SECS", PARAM_NAME_SIZE);
	_params[ind].param_type = PARAM_INT32;
	_params[ind].param_group = PARAM_NAVIGATOR;
	_params[ind].i_default = 10;
	_params[ind].i_value = 10;
	ind++;

	//返航降落速度
	strncpy(_params[ind].param_name, "NAV_RTL_LANDDING_VEL_Z", PARAM_NAME_SIZE);
	_params[ind].param_type = PARAM_FLOAT32;
	_params[ind].param_group = PARAM_NAVIGATOR;
	_params[ind].f_default = 0.5f;
	_params[ind].f_value = 0.3;
	ind++;

	//返航前刹车接受速度XY
	strncpy(_params[ind].param_name, "NAV_RTL_REACHED_VEL_XY", PARAM_NAME_SIZE);
	_params[ind].param_type = PARAM_FLOAT32;
	_params[ind].param_group = PARAM_NAVIGATOR;
	_params[ind].f_default = 0.5f;
	_params[ind].f_value = 0.5;
	ind++;

	//返航前刹车接受速度Z
	strncpy(_params[ind].param_name, "NAV_RTL_REACHED_VEL_Z", PARAM_NAME_SIZE);
	_params[ind].param_type = PARAM_FLOAT32;
	_params[ind].param_group = PARAM_NAVIGATOR;
	_params[ind].f_default = 0.5f;
	_params[ind].f_value = 0.5;
	ind++;

	_param_head.param_count = ind;
	for (int i = 0; i < _param_head.param_count; i++)
	{
		_params[i].param_index = i;
		_params[i].param_count = _param_head.param_count;
	}
}

int param_load(void)
{
	if (_params == NULL)
	{
		printf("[param] load error params is null.\n");
		return -1;
	}

	FILE *fp = fopen(PARAM_SAVE_PATH, "r");
	if (fp == NULL)
	{
		printf("[param] open params file error.\n");
		return -1;
	}

	int len = fread(&_param_head, sizeof(param_head_s), 1, fp);
	if (len != 1)
	{
		printf("[param] load params file error.\n");
		fclose(fp);
		return -1;
	}

	printf("[param] count %d\n", _param_head.param_count);
	for (int i = 0; i < _param_head.param_count; i++)
	{
		len = fread(&_params[i], sizeof(param_s), 1, fp);
		if (len != 1)
		{
			break;
		}
		printf("%s %d / %d ", _params[i].param_name, _params[i].param_index, _params[i].param_count);
		if (_params[i].param_type == PARAM_INT32)
		{
			printf("[%d %d]", _params[i].i_default, _params[i].i_value);
		}
		if (_params[i].param_type == PARAM_UINT32)
		{
			printf("[%u %u]", _params[i].u_default, _params[i].u_value);
		}
		if (_params[i].param_type == PARAM_FLOAT32)
		{
			printf("[%f %f]", _params[i].f_default, _params[i].f_value);
		}
		printf("\n");
	}
	fclose(fp);
}

int param_save(void)
{
	if (_params == NULL)
	{
		printf("[param] save error params is null.\n");
		return -1;
	}

	FILE *fp = fopen(PARAM_SAVE_PATH, "w+");
	if (fp == NULL)
	{
		printf("[param] open params file error.\n");
		return -1;
	}

	int len = fwrite(&_param_head, sizeof(param_head_s), 1, fp);
	if (len != 1)
	{
		printf("[param] save params file error.\n");
		fclose(fp);
		return -1;
	}

	for (int i = 0; i < _param_head.param_count; i++)
	{
		len = fwrite(&_params[i], sizeof(param_s), 1, fp);
		if (len != 1)
		{
			printf("[param] write param %d error.\n", i);
			break;
		}
	}
	fclose(fp);

	printf("[param] save params done.\n");
}

int param_get(const char *param_name, void *param_value)
{
	for (int i = 0; i < _param_head.param_count; i++)
	{
		if (strcmp(param_name, _params[i].param_name) == 0)
		{
			if (_params[i].param_type == PARAM_INT32)
			{
				memcpy(param_value, &_params[i].i_value, sizeof(_params[i].i_value));
				return 0;
			}
			if (_params[i].param_type == PARAM_UINT32)
			{
				memcpy(param_value, &_params[i].u_value, sizeof(_params[i].u_value));
				return 0;
			}
			if (_params[i].param_type == PARAM_FLOAT32)
			{
				memcpy(param_value, &_params[i].f_value, sizeof(_params[i].f_value));
				return 0;
			}
		}
	}
	printf("[param] can not find this param %s\n", param_name);
	return -1;
}

int param_set(const char *param_name, void *param_value)
{
	for (int i = 0; i < _param_head.param_count; i++)
	{
		if (strcmp(param_name, _params[i].param_name) == 0)
		{
			if (_params[i].param_type == PARAM_INT32)
			{
				memcpy(&_params[i].i_value, param_value, sizeof(_params[i].i_value));
				return 0;
			}
			if (_params[i].param_type == PARAM_UINT32)
			{
				memcpy(&_params[i].u_value, param_value, sizeof(_params[i].u_value));
				return 0;
			}
			if (_params[i].param_type == PARAM_FLOAT32)
			{
				memcpy(&_params[i].f_value, param_value, sizeof(_params[i].f_value));
				return 0;
			}
		}
	}
	printf("[param] can not find this param %s\n", param_name);
	return -1;
}

