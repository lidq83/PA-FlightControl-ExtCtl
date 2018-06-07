/*
 * extctl_sp.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_sp.h"

extern bool _extctl_should_exit;

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
	return 0;
}
