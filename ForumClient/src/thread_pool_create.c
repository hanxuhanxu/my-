#include "../include/thread_pool.h"


thread_pool_t * thread_pool_create(int min,int max ,int quemax)
{
		int err;
		thread_pool_t * pool;
		//pthread_mutex_init(&accept_lock,NULL);
		if((pool = (thread_pool_t *)malloc(sizeof(thread_pool_t)))==NULL){
				perror("thread pool create pool Malloc error");
				return NULL;
		}
		pool->thread_max = max;
		pool->thread_min = min;
		pool->thread_alive = 0;
		pool->thread_busy = 0;
		pool->thread_shutdown = TRUE;
		pool->queue_max = quemax;
		pool->queue_cur = 0;
		pool->queue_front = 0;
		pool->queue_rear = 0;
		if((pool->tids = (pthread_t *)malloc(sizeof(pthread_t) * max))==NULL){
				perror("thread pool create tids Malloc error");
				return NULL;
		}
		memset(pool->tids,0,sizeof(pthread_t) * max);
		//锁与条件变量初始化
		if(pthread_mutex_init(&pool->lock,NULL)!=0 || pthread_cond_init(&pool->not_full,NULL)!=0 || pthread_cond_init(&pool->not_empty,NULL)!=0){
				printf(" Init lock or cond Error\n");
				return NULL;
		}
		if((pool->queue_task = (task_t *)malloc(sizeof(task_t) * quemax))==NULL){
				perror("thread pool create queue_task  Malloc error");
				return NULL;
		}
		//管理者线程创建
		if((err = pthread_create(&pool->manager_id,NULL,thread_manager,(void *)pool))>0){
				printf("thread_create pthread_create manager error:%s\n",strerror(err));
				return NULL;
		}
		//消费线程创建
		for(int i=0;i<min;i++){
				if((err = pthread_create(&pool->tids[i],NULL,thread_custom,(void *)pool))>0){
						printf("thread_create pthread_create custmo error:%s\n",strerror(err));
						return NULL;
				}
				++pool->thread_alive;
		}
		return pool;
}
