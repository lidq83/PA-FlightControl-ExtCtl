/*
 * commander_status_machine.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_MAVIGATOR_NAV_STATUS_MACHINE_H_
#define SRC_MODULES_MAVIGATOR_NAV_STATUS_MACHINE_H_

#include <navigator.h>
#include <orb_manager.h>
#include <nav_block_reached.h>
#include <nav_block_init.h>
#include <nav_block_takeoff.h>
#include <nav_block_mission.h>
#include <nav_block_loiter.h>
#include <nav_block_rtl.h>
#include <nav_block_failoff.h>
#include <nav_block_failsafe.h>


#include <uORB/topics/ext_cmd.h>
#include <uORB/topics/ext_sys_status.h>
#include <uORB/topics/main_state.h>
#include <uORB/topics/nav_state.h>

typedef struct nav_state_block_s
{
	void (*p_on_init)(void);
	void (*p_on_desc)(void);
	void (*p_on_inactive)(void);
	void (*p_on_activation)(void);
	void (*p_on_active)(void);
	bool (*p_is_finished)(void);
} nav_state_block_s;

void nav_st_machine_init(void);

void nav_st_machine_run(void);

#endif /* SRC_MODULES_COMMANDER_STATUS_MACHINE_H_ */
