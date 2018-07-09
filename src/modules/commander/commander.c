/*
 * commander.c
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#include <commander.h>

static int commander_auto(void *arg);

static int commander_start(void *arg);

int commander_auto(void *arg)
{
	st_machine_init();

	st_machine_run();

	return 0;
}


int commander_start(void *arg)
{
	while (1)
	{
		usleep(100 * 1000);
	}

	return 0;
}

int commander_main(int argc, char *argv[])
{
	pthread_t pthddr;
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &commander_start, NULL);
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &commander_auto, NULL);

	return 0;
}
