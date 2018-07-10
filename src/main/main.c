/*
 * main.c
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#include <main.h>

int main(int argc, char *argv[])
{
	printf("[PA3] Start...\n");

	hrt_init();

	param_init();

	param_save();

	param_load();

	orb_main(argc, argv);

	extctl_main(argc, argv);

	commander_main(argc, argv);

	navigator_main(argc, argv);

	hrt_abstime time_begin = hrt_absolute_time();

	while (1)
	{
		hrt_abstime time_started = hrt_elapsed_time(time_begin);
		//printf("[main] started by %d secs.\n", time_started / 1000000);
		sleep(10);
	}

	return 0;
}
