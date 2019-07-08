#pragma once
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
#include "wrap.h"


#ifndef __THREAD_POOL_H_
#define __THREAD_POOL_H_

#define	TRUE 1
#define	FALSE 0

//pthread_mutex_t accept_lock;

struct task_t
{
	void * (*Job)(void*);
	void * arg;
};

struct thread_pool_t
{
	int thread_max;
	int thread_min;
	int thread_alive;
	int thread_busy;
	int thread_exitno;
	int thread_shutdown;
	int queue_max;
	int queue_cur;
	int queue_front;
	int queue_rear;
	
	pthread_t manager_id;
	pthread_t * tids;
	pthread_mutex_t lock;
	pthread_cond_t not_full;
	pthread_cond_t not_empty;
	task_t * queue_task;
};

//线程池创建初始化
thread_pool_t * thread_pool_create(int ,int,int);
//线程池回收资源释放
int thread_pool_destroy(thread_pool_t *);
//生产者任务
int thread_add_task(thread_pool_t *,task_t);
//消费者任务
void * thread_custom(void *);
void * thread_manager(void *);
int if_test_alive(pthread_t);
//int thread_socket_init(void);
//用户任务
void * thread_userwork(void *);

#endif
