/*
 * extctl_land.c
 *
 *  Created on: Jun 7, 2018
 *      Author: lidq
 */

#include "extctl_land.h"

//#define __EXTCTL_DEBUG_

static bool _wasland = true;

int extctl_land_handle(void *data)
{
	land_s *land = data;
	if (land == NULL)
	{
		return -1;
	}

	if (_wasland != land->landed)
	{
		if (land->landed)
		{
			extctl_cmd_disarm();
		}
		_wasland = land->landed;
	}

	return 0;
}

int extctl_land_send(void)
{
	return 0;
}

