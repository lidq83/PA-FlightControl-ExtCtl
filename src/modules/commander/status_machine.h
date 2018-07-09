/*
 * commander_status_machine.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_COMMANDER_STATUS_MACHINE_H_
#define SRC_MODULES_COMMANDER_STATUS_MACHINE_H_

#include <orb_manager.h>
#include <uORB/topics/ext_cmd.h>
#include <uORB/topics/ext_sys_status.h>
#include <uORB/topics/main_state.h>

#define ARMING_STATE_STANDBY							(1)

#define VEHICLE_CMD_COMPONENT_ARM_DISARM				(400)
#define VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_ARM		(1)
#define VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_DISARM	(0)

#define VEHICLE_CMD_DO_SET_MODE							(176)
#define VEHICLE_CMD_DO_SET_MODE_CUSTOM_ENABLE			(1)
#define VEHICLE_CMD_DO_SET_MODE_CUSTOM_MAIN_EXTCTL		(10)

void st_machine_init(void);

void st_machine_run(void);

#endif /* SRC_MODULES_COMMANDER_STATUS_MACHINE_H_ */
