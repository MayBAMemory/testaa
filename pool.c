#include "head.h"

int initPool(pool_t *status, int num){
  status->exitFlag = 0;
  status->threadNum = num;
  status->threadIds = calloc(num,sizeof(pthread_t));
  for(int i = 0; i < num; i++){
    pthread_create(&status->threadIds[i],NULL,threadMain,status);
    printf("created a thread\n");
  }
  //记录线程个数
  status->threadNum = num;

  //队列置空
  memset(&status->queue, 0, sizeof(status->queue));

  //初始化锁与条件变量
  pthread_mutex_init(&status->pool_lock,NULL);
  pthread_cond_init(&status->cond, NULL);

  return 0;
}

