/*
 * navigator.c
 *
 *  Created on: Jul 6, 2018
 *      Author: lidq
 */

#include <navigator.h>

static orb_advert_t _pub_sp = NULL;
static ext_vehicle_pos_s _curr_pos;
static main_state_s _main_state;
static nav_state_s _nav_state;

static int navigator_start(void *arg);

static int navigator_run(void *arg);

int navigator_start(void *arg)
{
	_pub_sp = orb_advertise(ORB_ID(ext_vehicle_sp));

	nav_st_machine_init();

	nav_st_machine_run();

	return 0;
}

int navigator_run(void *arg)
{
	orb_advert_t sub_pos_state = orb_subscribe(ORB_ID(ext_vehicle_pos));
	orb_advert_t sub_main_state = orb_subscribe(ORB_ID(main_state));
	orb_advert_t sub_nav_state = orb_subscribe(ORB_ID(nav_state));

	while (1)
	{
		bool updated = false;

		orb_check(sub_pos_state, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(ext_vehicle_pos), sub_pos_state, &_curr_pos);
		}

		orb_check(sub_main_state, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(main_state), sub_main_state, &_main_state);
		}

		orb_check(sub_nav_state, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(nav_state), sub_nav_state, &_nav_state);
		}

		usleep(100 * 1000);
	}

	return 0;
}

ext_vehicle_pos_s *navigator_get_curr_pos(void)
{
	return &_curr_pos;
}

main_state_s *navigator_get_main_state(void)
{
	return &_main_state;
}

nav_state_s *navigator_get_nav_state(void)
{
	return &_nav_state;
}

void navigator_set_sp(ext_vehicle_sp_s *sp)
{
	orb_publish(ORB_ID(ext_vehicle_sp), _pub_sp, sp);
}

int navigator_main(int argc, char *argv[])
{
	pthread_t pthddr;
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &navigator_start, NULL);
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &navigator_run, NULL);

	return 0;
}
