/*
 * commander.h
 *
 *  Created on: Jul 5, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_COMMANDER_COMMANDER_H_
#define SRC_MODULES_COMMANDER_COMMANDER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <orb_manager.h>
#include <uORB/topics/survey_information.h>

int commander_main(int argc, char *argv[]);

#endif /* SRC_MODULES_COMMANDER_COMMANDER_H_ */
