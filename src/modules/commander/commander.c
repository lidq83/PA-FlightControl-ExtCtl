/*
 * commander.c
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#include <commander.h>

static int commander_start(void *arg);

static int commander_run(void *arg);

int commander_start(void *arg)
{
	cmd_st_machine_init();

	cmd_st_machine_run();

	return 0;
}

static int commander_run(void *arg)
{
	char cmd[0x100];

	while (1)
	{
		printf("pa3> ");
		scanf("%s", cmd);

		if (strcmp(cmd, "takeoff") == 0)
		{
			if (cmd_st_get_main_state() == MAIN_STATE_STANDBY)
			{
				cmd_st_set_main_state(MAIN_STATE_AUTO_FLY);

				cmd_st_set_nav_state(NAV_STATE_TAKEOFF);
			}
			else
			{
				printf("[cmd] Error %x.\n", NAV_STATE_TAKEOFF);
			}
		}

		if (strcmp(cmd, "failoff") == 0)
		{
			if (cmd_st_get_main_state() == MAIN_STATE_AUTO_FLY)
			{
				cmd_st_set_nav_state(NAV_STATE_FAILOFF);
			}
			else
			{
				printf("[cmd] Error %x.\n", NAV_STATE_FAILOFF);
			}
		}

		if (strcmp(cmd, "rtl") == 0)
		{
			if (cmd_st_get_main_state() == MAIN_STATE_AUTO_FLY)
			{
				cmd_st_set_nav_state(NAV_STATE_RTL);
			}
			else
			{
				printf("[cmd] Error %x.\n", NAV_STATE_RTL);
			}
		}

		if (strcmp(cmd, "mission") == 0)
		{
//			if (cmd_st_get_main_state() == MAIN_STATE_STANDBY)
//			{
//				cmd_st_set_main_state(MAIN_STATE_AUTO_FLY);
//			}
			if (cmd_st_get_main_state() == MAIN_STATE_AUTO_FLY)
			{
				cmd_st_set_nav_state(NAV_STATE_MISSION);
			}
			else
			{
				printf("[cmd] Error %x.\n", NAV_STATE_MISSION);
			}
		}

		if (strcmp(cmd, "loiter") == 0)
		{
			if (cmd_st_get_main_state() == MAIN_STATE_AUTO_FLY)
			{
				cmd_st_set_nav_state(NAV_STATE_LOITER);
			}
			else
			{
				printf("[cmd] Error %x.\n", NAV_STATE_LOITER);
			}
		}

		usleep(100 * 1000);
	}
}

int commander_main(int argc, char *argv[])
{
	pthread_t pthddr;
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &commander_start, NULL);
	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &commander_run, NULL);

	return 0;
}
