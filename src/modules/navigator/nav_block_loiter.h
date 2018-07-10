/*
 * nav_block_loiter.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_LOITER_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_LOITER_H_

#include "nav_status_machine.h"

void nav_loiter_on_init(void);

void nav_loiter_on_desc(void);

void nav_loiter_on_inactive(void);

void nav_loiter_on_activation(void);

void nav_loiter_on_active(void);

bool nav_loiter_is_finished(void);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_LOITER_H_ */
