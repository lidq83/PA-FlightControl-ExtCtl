/*
 * extctl_sp.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_sp.h"

extern bool _extctl_should_exit;
static orb_advert_t _orb_sp = NULL;
static ext_vehicle_sp_s _sp = { 0 };

int extctl_sp_init(void)
{
	_orb_sp = orb_subscribe(ORB_ID(ext_vehicle_sp));
	return 0;
}

int extctl_sp_send(void)
{
	while (!_extctl_should_exit)
	{
		bool updated = false;
		orb_check(_orb_sp, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(ext_vehicle_sp), _orb_sp, &_sp);
		}

		extctl_protocal_write(&_sp, DATA_TYPE_SP, sizeof(ext_vehicle_sp_s));
		usleep(DEV_RATE_SP);
	}
	return 0;
}
