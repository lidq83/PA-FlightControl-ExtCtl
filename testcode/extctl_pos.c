/*
 * extctl_pos.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_pos.h"

extern bool _extctl_should_exit;

int extctl_pos_handle(void *data)
{
	vehicle_pos_s *pos = data;
	if (pos == NULL)
	{
		return -1;
	}

	printf("%5.2f %5.2f %5.2f %12.8f %12.8f %5.2f\n", pos->x, pos->y, pos->z, pos->lat, pos->lon, pos->alt);

	return 0;
}

int extctl_pos_send(void)
{
	return 0;
}
