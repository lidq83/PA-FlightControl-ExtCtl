/*
 * extctl_pos.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_pos.h"

extern bool _extctl_should_exit;
static orb_advert_t _orb_pos = NULL;
static ext_vehicle_pos_s _pos = { 0 };

int extctl_pos_init(void)
{
	_orb_pos = orb_advertise(ORB_ID(ext_vehicle_pos));

	return 0;
}

int extctl_pos_handle(void *data)
{
	ext_vehicle_pos_s *pos = data;
	if (pos == NULL)
	{
		return -1;
	}
	memcpy(&_pos, pos, sizeof(ext_vehicle_pos_s));
	orb_publish(ORB_ID(ext_vehicle_pos), _orb_pos, &_pos);

	return 0;
}
