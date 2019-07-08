#include "../include/thread_pool.h"


void * thread_custom(void * arg)
{
		pthread_detach(pthread_self());
		thread_pool_t * pool = (thread_pool_t *)arg;
		task_t task;
		printf("------------> Custom tid [0x%x] Waiting...\n",(unsigned int)pthread_self());
		while(pool->thread_shutdown){
				pthread_mutex_lock(&pool->lock);
				if(pool->queue_cur == 0){
						pthread_cond_wait(&pool->not_empty,&pool->lock);
						printf("Custom Working...\n");
						if(!pool->thread_shutdown || pool->thread_exitno > 0){
								printf("------------> Custom tid [0x%x] Exiting...\n",(unsigned int)pthread_self());
								--pool->thread_alive;
								--pool->thread_exitno;
								pthread_mutex_unlock(&pool->lock);
								pthread_exit(NULL);
						}
				}
				task.Job = pool->queue_task[pool->queue_rear].Job;
				task.arg = pool->queue_task[pool->queue_rear].arg;
				pool->queue_rear = (pool->queue_rear + 1) % pool->queue_max;
				--pool->queue_cur;
				++pool->thread_busy;
				pthread_cond_signal(&pool->not_full);
				pthread_mutex_unlock(&pool->lock);
				task.Job(task.arg);
				pthread_mutex_lock(&pool->lock);
				--pool->thread_busy;
				pthread_mutex_unlock(&pool->lock);
		}
		pthread_exit(NULL);
}
