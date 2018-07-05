/*
 * extctl_socket.h
 *
 *  Created on: Jun 26, 2018
 *      Author: lidq
 */

#ifndef EXTCTL_EXTCTL_SOCKET_H_
#define EXTCTL_EXTCTL_SOCKET_H_

#include "extctl_typedef.h"

#ifdef __USE_SOCKET

int client_start(void);

static int make_socket_non_blocking(int sfd);

static void client_exception(void);

#endif

#endif /* EXTCTL_EXTCTL_SOCKET_H_ */
