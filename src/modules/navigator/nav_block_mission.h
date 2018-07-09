/*
 * nav_block_mission.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_MISSION_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_MISSION_H_

#include "nav_status_machine.h"

void nav_mission_on_inactive(void);

void nav_mission_on_activation(void);

void nav_mission_on_active(void);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_MISSION_H_ */
