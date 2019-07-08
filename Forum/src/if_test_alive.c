#include"../include/thread_pool.h"
int if_test_alive(pthread_t tid)
{
		if((pthread_kill(tid,0))==-1){
				if(errno == ESRCH)
						return 0;
		}
		return 1;
}
