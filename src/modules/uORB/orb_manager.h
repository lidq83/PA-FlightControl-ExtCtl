/*
 * orb_manager.h
 *
 *  Created on: May 16, 2018
 *      Author: lidq
 */

#ifndef SRC_MODULES_UORB_ORB_MANAGER_H_
#define SRC_MODULES_UORB_ORB_MANAGER_H_

#include <orb_typedef.h>
#include <hrt.h>
#include <uORB/uORB.h>

int orb_main(int argc, char *argv[]);

orb_advert_t orb_advertise(const struct orb_metadata *meta);

int orb_unadvertise(orb_advert_t orb_adv);

int orb_publish(const struct orb_metadata *meta, orb_advert_t orb_adv, void *data);

orb_advert_t orb_subscribe(const struct orb_metadata *meta);

int orb_unsubscribe(orb_advert_t orb_adv);

int orb_check(orb_advert_t orb_adv, bool *updated);

int orb_copy(const struct orb_metadata *meta, orb_advert_t orb_adv, void *data);

#endif /* SRC_GORB_GORB_MANAGER_H_ */
