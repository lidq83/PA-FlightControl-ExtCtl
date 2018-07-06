/*
 * extctl_status.c
 *
 *  Created on: Jun 14, 2018
 *      Author: lidq
 */

#include "extctl_status.h"

extern bool _extctl_should_exit;
static orb_advert_t _orb_st = NULL;
ext_sys_status_s _status = { 0 };

//static bool _wasland = true;

int extctl_status_init(void)
{
	_orb_st = orb_advertise(ORB_ID(ext_sys_status));

	return 0;
}

int extctl_status_handle(void *data)
{
	ext_sys_status_s *status = data;
	if (status == NULL)
	{
		return -1;
	}
	memcpy(&_status, status, sizeof(ext_sys_status_s));

	orb_publish(ORB_ID(ext_sys_status), _orb_st, &_status);

//	if (_wasland != _status.landed)
//	{
//		if (_status.landed)
//		{
//			extctl_cmd_disarm();
//		}
//		_wasland = _status.landed;
//	}

	return 0;
}

