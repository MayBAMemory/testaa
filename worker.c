#include "head.h"

void *threadMain(void *p) {
  pool_t *pool = p;

  while (1) {
    pthread_mutex_lock(&pool->pool_lock);
    int netFd;
    /*while (pool->queue.size <= 0 && pool->exitFlag ==0) {
      pthread_cond_wait(&pool->cond, &pool->pool_lock);
    }*///无任务时锁上
    //有任务了,接收队头任务
    if(pool->exitFlag ==1){
      printf("son thread exiting...\n");
      pthread_mutex_unlock(&pool->pool_lock);
      pthread_exit(NULL);
    }
    netFd = pool->queue.head->netFd;

    deQuene(&pool->queue);
    pthread_mutex_unlock(&pool->pool_lock);

    sendBFile(netFd);
    close(netFd);
  }
  return NULL;
}
