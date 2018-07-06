/*
 * navigator.h
 *
 *  Created on: Jul 6, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAVIGATOR_H_
#define SRC_MODULES_NAVIGATOR_NAVIGATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <orb_manager.h>
#include <uORB/topics/ext_sys_status.h>
#include <uORB/topics/ext_vehicle_pos.h>

int navigator_main(int argc, char *argv[]);

#endif /* SRC_MODULES_NAVIGATOR_NAVIGATOR_H_ */
