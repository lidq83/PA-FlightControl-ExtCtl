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
#include <uORB/topics/ext_vehicle_sp.h>
#include <uORB/topics/main_state.h>
#include <uORB/topics/nav_state.h>
#include <nav_status_machine.h>

ext_vehicle_pos_s *navigator_get_curr_pos(void);

main_state_s *navigator_get_main_state(void);

nav_state_s *navigator_get_nav_state(void);

void navigator_set_nav_state(uint8_t nav_state);

void navigator_set_sp(ext_vehicle_sp_s *sp);

int navigator_main(int argc, char *argv[]);

#endif /* SRC_MODULES_NAVIGATOR_NAVIGATOR_H_ */
