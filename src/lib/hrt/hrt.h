/*
 * hrt.h
 *
 *  Created on: Jul 6, 2018
 *      Author: lidq
 */

#ifndef SRC_LIB_HRT_HRT_H_
#define SRC_LIB_HRT_HRT_H_

#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>

typedef uint64_t hrt_abstime;

void hrt_init(void);

hrt_abstime hrt_absolute_time(void);

hrt_abstime hrt_elapsed_time(hrt_abstime then);

hrt_abstime hrt_betwen_time(hrt_abstime t1, hrt_abstime t2);

#endif /* SRC_LIB_HRT_HRT_H_ */
