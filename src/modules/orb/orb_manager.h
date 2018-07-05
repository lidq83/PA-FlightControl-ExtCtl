/*
 * orb_manager.h
 *
 *  Created on: May 16, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_ORB_ORB_MANAGER_H_
#define SRC_MODULES_ORB_ORB_MANAGER_H_

#include <orb_typedef.h>

int orb_main(int argc, char *argv[]);

int orb_advertise(const struct orb_metadata *meta);

int orb_unadvertise(int fd);

int orb_publish(const struct orb_metadata *meta, int fd, void *data);

int orb_subscribe(const struct orb_metadata *meta);

int orb_unsubscribe(int fd);

int orb_check(int fd, bool *updated);

int orb_copy(const struct orb_metadata *meta, int fd, void *data);

#endif /* SRC_GORB_GORB_MANAGER_H_ */
