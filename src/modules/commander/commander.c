/*
 * commander.c
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#include <commander.h>

//void cmd_test01(void)
//{
//	struct survey_information_s si = { 0 };
//	orb_advert_t pub = orb_advertise(ORB_ID(survey_information));
//
//	uint64_t tt = 0;
//	while (1)
//	{
//		si.timestamp = tt++;
//		orb_publish(ORB_ID(survey_information), pub, &si);
//		printf("[commander] si 1 tt %6u.\n", si.timestamp);
//		usleep(10 * 1000);
//	}
//}
//
//void cmd_test02(void)
//{
//	struct survey_information_s si = { 0 };
//	orb_advert_t sub = orb_subscribe(ORB_ID(survey_information));
//	while (1)
//	{
//		bool updated = false;
//		orb_check(sub, &updated);
//		if (updated)
//		{
//			orb_copy(ORB_ID(survey_information), sub, &si);
//			printf("[commander] si 2 tt %6u.\n", si.timestamp);
//		}
//		usleep(10 * 1000);
//	}
//}
//
//void cmd_test03(void)
//{
//	struct survey_information_s si = { 0 };
//	orb_advert_t sub = orb_subscribe(ORB_ID(survey_information));
//
//	while (1)
//	{
//		bool updated = false;
//		orb_check(sub, &updated);
//		if (updated)
//		{
//			orb_copy(ORB_ID(survey_information), sub, &si);
//			printf("[commander] si 3 tt %6u.\n", si.timestamp);
//		}
//		usleep(10 * 1000);
//	}
//}

int commander_main(int argc, char *argv[])
{
//	pthread_t pthddr;
//	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &cmd_test01, NULL);
//	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &cmd_test02, NULL);
//	pthread_create(&pthddr, (const pthread_attr_t*) NULL, (void* (*)(void*)) &cmd_test03, NULL);

	return 0;
}
