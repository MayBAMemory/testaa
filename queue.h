#ifndef __THREADQUEUE__
#define __THREADQUEUE__
#include <my_header.h>

typedef struct node_s{
  int netFd;
  struct node_s *pNext;
}node_t;

typedef struct queue_s{
  node_t *head;
  node_t *end;
  int size;
}queue_t;

int enQuene(queue_t *pQueue, int net_fd); 
int deQuene(queue_t *pQueue);

#endif
