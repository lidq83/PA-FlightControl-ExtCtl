/*
 * commander.c
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#include <commander.h>

int commander_main(int argc, char *argv[])
{
	orb_advertise(ORB_ID(survey_information));

	printf("[commander] main running.\n");

	return 0;
}
