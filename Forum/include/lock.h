
#pragma once
#ifndef _LOCK_H_
#define _LOCK_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>

extern pthread_mutex_t accept_lock;
#endif
