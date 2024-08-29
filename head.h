#ifndef __THREADHEAD__
#define __THREADHEAD__
#include <my_header.h>
#include "queue.h"

typedef struct pool_s{
  //存储所有子线程id
  pthread_t *threadIds;

  //子线程的数量
  int threadNum;

  //任务队列
  queue_t queue;

  //锁
  pthread_mutex_t pool_lock;

  //条件
  pthread_cond_t cond;
}pool_t;

int initSocket(int *socketFd, char *port, char *ip);

int epollAddFd(int epoll_fd, int fd);

int sendBFile(int netFd);

int initPool(pool_t *status, int num);

void * threadMain(void *p);//线程入口函数,传入status

#endif // !__THREADHEAD__


