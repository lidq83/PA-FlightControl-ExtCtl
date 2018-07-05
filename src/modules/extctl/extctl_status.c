/*
 * extctl_status.c
 *
 *  Created on: Jun 14, 2018
 *      Author: lidq
 */

#include "extctl_status.h"

extern bool _extctl_should_exit;
static bool _wasland = true;
sys_status_s _status = { 0 };

int extctl_status_handle(void *data)
{
	sys_status_s *status = data;
	if (status == NULL)
	{
		return -1;
	}
	memcpy(&_status, status, sizeof(sys_status_s));

	if (_wasland != _status.landed)
	{
		if (_status.landed)
		{
			extctl_cmd_disarm();
		}
		_wasland = _status.landed;
	}

	return 0;
}

int extctl_status_send(void)
{
	return 0;
}
