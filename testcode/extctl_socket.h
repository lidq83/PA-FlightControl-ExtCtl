/*
 * extctl_socket.h
 *
 *  Created on: Jun 26, 2018
 *      Author: lidq
 */

#ifndef TESTCODE_EXTCTL_SOCKET_H_
#define TESTCODE_EXTCTL_SOCKET_H_

#include "extctl_typedef.h"

#ifdef __PX4_POSIX

int client_start(void);

static int make_socket_non_blocking(int sfd);

static void client_exception(void);

#endif

#endif /* TESTCODE_EXTCTL_SOCKET_H_ */
