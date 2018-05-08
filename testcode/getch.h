/*
 * getch.h
 *
 *  Created on: May 11, 2016
 *
 *  四轴飞行控制器  Copyright (C) 2016  李德强
 */

#ifndef MODS_PARAMSCTL_GETCH_H_
#define MODS_PARAMSCTL_GETCH_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>

void initTermios(int32_t echo);

void resetTermios();

char getch_(int32_t echo);

char getch(void);

char getche(void);

#endif /* MODS_PARAMSCTL_GETCH_H_ */
