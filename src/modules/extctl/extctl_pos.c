/*
 * extctl_pos.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_pos.h"

extern bool _extctl_should_exit;
ext_vehicle_pos_s _pos = { 0 };

int extctl_pos_handle(void *data)
{
	ext_vehicle_pos_s *pos = data;
	if (pos == NULL)
	{
		return -1;
	}
	memcpy(&_pos, pos, sizeof(ext_vehicle_pos_s));

	return 0;
}

int extctl_pos_send(void)
{
	return 0;
}
