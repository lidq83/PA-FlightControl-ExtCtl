/*
 * nav_block_init.h
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_NAVIGATOR_NAV_BLOCK_INIT_H_
#define SRC_MODULES_NAVIGATOR_NAV_BLOCK_INIT_H_

#include "nav_status_machine.h"

void nav_init_on_init(void);

void nav_init_on_desc(void);

void nav_init_on_inactive(void);

void nav_init_on_activation(void);

void nav_init_on_active(void);

bool nav_init_is_finished(void);

#endif /* SRC_MODULES_NAVIGATOR_NAV_BLOCK_INIT_H_ */
