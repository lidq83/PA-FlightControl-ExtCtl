/*
 * commander_status_machine.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_COMMANDER_CMD_STATUS_MACHINE_H_
#define SRC_MODULES_COMMANDER_CMD_STATUS_MACHINE_H_

#include <commander.h>

#define MAIN_STATE_EXTCTL								(13)
#define ARMING_STATE_STANDBY							(1)

#define VEHICLE_CMD_COMPONENT_ARM_DISARM				(400)
#define VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_ARM		(1)
#define VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_DISARM	(0)

#define VEHICLE_CMD_DO_SET_MODE							(176)
#define VEHICLE_CMD_DO_SET_MODE_CUSTOM_ENABLE			(1)
#define VEHICLE_CMD_DO_SET_MODE_CUSTOM_MAIN_EXTCTL		(10)

void cmd_st_machine_init(void);

void cmd_st_machine_run(void);

uint8_t cmd_st_get_main_state(void);

void cmd_st_set_main_state(uint8_t main_state);

uint8_t cmd_st_get_nav_state(void);

void cmd_st_set_nav_state(uint8_t nav_state);

#endif /* SRC_MODULES_COMMANDER_CMD_STATUS_MACHINE_H_ */
