/*
 * nav_block_takeoff.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_TAKEOFF_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_TAKEOFF_H_

#include "nav_status_machine.h"

void nav_takeoff_on_inactive(void);

void nav_takeoff_on_activation(void);

void nav_takeoff_on_active(void);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_TAKEOFF_H_ */
