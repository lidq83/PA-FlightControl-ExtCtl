/*
 * commander.c
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#include <commander.h>

void cmd_test01(void)
{
	vehicle_pos_s pos = { 0 };
	orb_advert_t pub = orb_advertise(ORB_ID(vehicle_pos));
	uint64_t tt = 0;
	while (1)
	{
		pos.timestamp = tt++;
		orb_publish(ORB_ID(vehicle_pos), pub, &pos);
		//printf("[commander] si 1 tt %6u.\n", pos.timestamp);
		usleep(10 * 1000);
	}
}

void cmd_test02(void)
{
	vehicle_pos_s pos = { 0 };
	orb_advert_t sub = orb_subscribe(ORB_ID(vehicle_pos));
	while (1)
	{
		bool updated = false;
		//printf("sub02 %p %p\n", sub, ((s_orb_sub *)sub)->pub);
		orb_check(sub, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(vehicle_pos), sub, &pos);
			//printf("[commander] si 2 tt %6u.\n", pos.timestamp);
		}
		usleep(10 * 1000);
	}
}

void cmd_test03(void)
{
	vehicle_pos_s pos = { 0 };
	orb_advert_t sub = orb_subscribe(ORB_ID(vehicle_pos));
	while (1)
	{
		bool updated = false;
		//printf("sub03 %p %p\n", sub, ((s_orb_sub *)sub)->pub);
		orb_check(sub, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(vehicle_pos), sub, &pos);
			//printf("[commander] si 3 tt %6u.\n", pos.timestamp);
		}
		usleep(10 * 1000);
	}
}

int commander_main(int argc, char *argv[])
{
	pthread_t pthddr;
//	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &cmd_test02, NULL);
//	usleep(1000);
//	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &cmd_test03, NULL);
//	usleep(1000);
//	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &cmd_test01, NULL);

	printf("%d\n", sizeof(vehicle_pos_s));

	return 0;
}
