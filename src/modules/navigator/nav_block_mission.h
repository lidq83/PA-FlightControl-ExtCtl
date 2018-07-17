/*
 * nav_block_mission.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_MISSION_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_MISSION_H_

#include <airline.h>
#include "nav_status_machine.h"

void nav_mission_on_init(void);

void nav_mission_on_desc(void);

void nav_mission_on_inactive(void);

void nav_mission_on_activation(void);

void nav_mission_on_active(void);

bool nav_mission_is_finished(void);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_MISSION_H_ */
