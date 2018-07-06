/*
 * commander.c
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#include <commander.h>

static int commander_start(void *arg);

int commander_start(void *arg)
{
	ext_sys_status_s st = { 0 };
	orb_advert_t sub_st = orb_subscribe(ORB_ID(ext_sys_status));
	bool wasland = true;

	while (1)
	{
		bool updated = false;
		orb_check(sub_st, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(ext_sys_status), sub_st, &st);

			if (wasland != st.landed)
			{
				if (st.landed)
				{
					extctl_cmd_disarm();
				}
				wasland = st.landed;
			}
		}
		usleep(100 * 1000);
	}

	return 0;
}

int commander_main(int argc, char *argv[])
{
	pthread_t pthddr;
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &commander_start, NULL);

	return 0;
}
