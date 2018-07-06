/*
 * hrt.c
 *
 *  Created on: Jul 6, 2018
 *      Author: lidq
 */

#include <hrt.h>

static struct timeval timers;
static sem_t _sem_hrt;

void hrt_init(void)
{
	sem_init(&_sem_hrt, 0, 1);
}

hrt_abstime hrt_absolute_time(void)
{
	sem_wait(&_sem_hrt);

	gettimeofday(&timers, NULL);
	hrt_abstime now = timers.tv_sec * 1000000 + timers.tv_usec;
	sem_post(&_sem_hrt);

	return now;
}

hrt_abstime hrt_elapsed_time(hrt_abstime then)
{
	hrt_abstime now = hrt_absolute_time();
	return now - then;
}

hrt_abstime hrt_betwen_time(hrt_abstime t1, hrt_abstime t2)
{
	return t1 - t2;
}
