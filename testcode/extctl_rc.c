/*
 * extctl_rc.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_rc.h"

extern bool _extctl_should_exit;

int extctl_rc_handle(void *data)
{
	rc_s *rc = data;
	if (rc == NULL)
	{
		return -1;
	}

	return 0;
}

int extctl_rc_send(void)
{
	return 0;
}
