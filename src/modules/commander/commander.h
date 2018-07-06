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
#include <uORB/topics/vehicle_pos.h>
#include "../uORB/orb_manager.h"

int commander_main(int argc, char *argv[]);

#endif /* SRC_MODULES_COMMANDER_COMMANDER_H_ */
