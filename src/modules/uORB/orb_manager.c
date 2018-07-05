/*
 * orb_manager.c
 *
 *  Created on: May 16, 2018
 *      Author: lidq
 */

#include "orb_manager.h"

//公告
int orb_advertise(const struct orb_metadata *meta)
{
	if (meta == NULL)
	{
		return -1;
	}
	printf("%s\n", meta->o_name);
	//printf("%s\n", meta->o_fields);
	//printf("%u\n", meta->o_size);
	//printf("%u\n", meta->o_size_no_padding);

	return 0;
}

int orb_unadvertise(const struct orb_metadata *meta)
{
	return 0;
}

int orb_subscribe(const struct orb_metadata *meta)
{
	return 0;
}

int orb_unsubscribe(int handle)
{
	return 0;
}

int orb_publish(const struct orb_metadata *meta, void *data)
{
	return 0;
}

int orb_check(int handle, bool *updated)
{
	return 0;
}

int orb_copy(const struct orb_metadata *meta, int handle, void *data)
{
	return 0;
}
