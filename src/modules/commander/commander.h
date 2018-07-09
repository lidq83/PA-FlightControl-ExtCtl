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
#include <uORB/topics/ext_cmd.h>
#include <uORB/topics/ext_sys_status.h>
#include <uORB/topics/main_state.h>
#include <uORB/topics/nav_state.h>
#include <cmd_status_machine.h>

int commander_main(int argc, char *argv[]);

#endif /* SRC_MODULES_COMMANDER_COMMANDER_H_ */
