#include "../include/thread_pool.h"


int thread_add_task(thread_pool_t * pool,task_t task)
{
		pthread_mutex_lock(&pool->lock);
		if(pool->thread_shutdown){
				if(pool->queue_cur == pool->queue_max){
						pthread_cond_wait(&pool->not_full,&pool->lock);
				}
				pool->queue_task[pool->queue_front].Job = task.Job;
				pool->queue_task[pool->queue_front].arg = task.arg;
				pool->queue_front = (pool->queue_front + 1) % pool->queue_max;
				++pool->queue_cur;
				pthread_cond_signal(&pool->not_empty);

		}else
		{
				return -1;
		}
		pthread_mutex_unlock(&pool->lock);

		return 0;
}
