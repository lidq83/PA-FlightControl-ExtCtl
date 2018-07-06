/*
 * extctl_rc.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_rc.h"

extern bool _extctl_should_exit;
static orb_advert_t _orb_rc = NULL;
static ext_rc_s _rc = { 0 };

int extctl_rc_init(void)
{
	_orb_rc = orb_advertise(ORB_ID(ext_rc));

	return 0;
}

int extctl_rc_handle(void *data)
{
	ext_rc_s *rc = data;
	if (rc == NULL)
	{
		return -1;
	}

	memcpy(&_rc, rc, sizeof(ext_rc_s));

	orb_publish(ORB_ID(ext_rc), _orb_rc, &_rc);

	return 0;
}

