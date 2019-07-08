#include "../include/thread_pool.h"

void * thread_manager(void * arg)
{
		pthread_detach(pthread_self());
		int alive;
		int busy;
		int cur;
		int add=0;
		int i=0;
		thread_pool_t * pool = (thread_pool_t *)arg;
		printf("------------> Manager tid [0x%x] Runing...\n",(unsigned int)pthread_self());
		while(pool->thread_shutdown){
				pthread_mutex_lock(&pool->lock);
				alive = pool->thread_alive;
				busy = pool->thread_busy;
				cur = pool->queue_cur;
				pthread_mutex_unlock(&pool->lock);
				if((cur >= alive - busy || (float)busy / alive * 100 >= (float)70) && alive + pool->thread_min <= pool->thread_max){
						for(i;(i<pool->thread_max,add < pool->thread_min);i++){
								if(pool->tids[i]==0||!if_test_alive(pool->tids[i]))
								{
										pthread_create(&pool->tids[i],NULL,thread_custom,(void*)pool);
										pthread_mutex_lock(&pool->lock);
										++pool->thread_alive;
										pthread_mutex_unlock(&pool->lock);
										add++;
								}
						}

				}
				if(busy * 2 < alive - busy && alive - pool->thread_min >= pool->thread_min){
						pool->thread_exitno = pool->thread_min;
						for(i=0;i<pool->thread_min;i++)
								pthread_cond_signal(&pool->not_empty);
				}
				printf("------------> Manager tid [0x%x] Output info [alive:%d busy:%d idle:%d b/a:%.2f%% a/m:%.2f%%]\n",(unsigned int)pthread_self(),alive,busy,alive-busy,(float)busy/alive*(float)100,(float)alive/pool->thread_max * (float)100);
				sleep(2);
		}
		pthread_exit(NULL);
}
