/*
 * navigator.c
 *
 *  Created on: Jul 6, 2018
 *      Author: lidq
 */

#include <navigator.h>

static int navigator_start(void *arg);

static void navigator_chk_status(orb_advert_t sub);

static void navigator_chk_pos(orb_advert_t sub);

int navigator_start(void *arg)
{
	orb_advert_t sub_st = orb_subscribe(ORB_ID(ext_sys_status));
	orb_advert_t sub_pos = orb_subscribe(ORB_ID(ext_vehicle_pos));

	while (1)
	{
		navigator_chk_status(sub_st);

		navigator_chk_pos(sub_pos);

		usleep(100 * 1000);
	}

	return 0;
}

void navigator_chk_status(orb_advert_t sub)
{
	ext_sys_status_s st = { 0 };
	bool updated = false;
	orb_check(sub, &updated);
	if (updated)
	{
		orb_copy(ORB_ID(ext_sys_status), sub, &st);
	}
}

void navigator_chk_pos(orb_advert_t sub)
{
	ext_vehicle_pos_s pos = { 0 };
	bool updated = false;
	orb_check(sub, &updated);
	if (updated)
	{
		orb_copy(ORB_ID(ext_vehicle_pos), sub, &pos);
	}
}

int navigator_main(int argc, char *argv[])
{
	pthread_t pthddr;
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &navigator_start, NULL);

	return 0;
}
