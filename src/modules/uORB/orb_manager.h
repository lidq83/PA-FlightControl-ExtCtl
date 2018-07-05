/*
 * orb_manager.h
 *
 *  Created on: May 16, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_UORB_ORB_MANAGER_H_
#define SRC_MODULES_UORB_ORB_MANAGER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "uORB.h"

int orb_advertise(const struct orb_metadata *meta);

int orb_unadvertise(const struct orb_metadata *meta);

int orb_subscribe(const struct orb_metadata *meta);

int orb_unsubscribe(int handle);

int orb_publish(const struct orb_metadata *meta, void *data);

int orb_check(int handle, bool *updated);

int orb_copy(const struct orb_metadata *meta, int handle, void *data);

#endif /* SRC_GORB_GORB_MANAGER_H_ */
