/*
 * nav_block_rtl.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_RTL_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_RTL_H_

#include "nav_status_machine.h"

typedef enum NAV_RTL_STATE
{
	NAV_RTL_STOP = 0,
	NAV_RTL_CLIMB,
	NAV_RTL_RET_HOME,
	NAV_RTL_TO_LOITER,
	NAV_RTL_LOITER,
	NAV_RTL_LANDING,
	NAV_RTL_FAILSAFE
} nav_rtl_state_s;

void nav_rtl_on_inactive(void);

void nav_rtl_on_activation(void);

void nav_rtl_on_active(void);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_RTL_H_ */
