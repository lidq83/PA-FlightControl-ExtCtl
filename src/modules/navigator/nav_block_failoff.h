/*
 * nav_block_failoff.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "nav_status_machine.h"

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_FAILOFF_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_FAILOFF_H_

void nav_failoff_on_init(void);

void nav_failoff_on_desc(void);

void nav_failoff_on_inactive(void);

void nav_failoff_on_activation(void);

void nav_failoff_on_active(void);

bool nav_failoff_is_finished(void);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_FAILOFF_H_ */
