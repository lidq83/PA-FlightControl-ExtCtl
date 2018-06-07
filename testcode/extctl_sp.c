/*
 * extctl_sp.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_sp.h"

extern bool _extctl_should_exit;
vehicle_sp_s _sp = { 0 };

int extctl_sp_handle(void *data)
{
	vehicle_sp_s *sp = data;
	if (sp == NULL)
	{
		return -1;
	}

	return 0;
}

int extctl_sp_send(void)
{
	while (!_extctl_should_exit)
	{
		send_data_buff(&_sp, DATA_TYPE_SP, sizeof(vehicle_sp_s));
		usleep(DEV_RATE_SP);
	}
	return 0;
}
