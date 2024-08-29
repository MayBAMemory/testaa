#include "queue.h"

int enQuene(queue_t *pQueue, int net_fd){
  node_t *pNew = calloc(1, sizeof(node_t));
  pNew->netFd = net_fd;

  if(pQueue->size == 0){//空队列
    pQueue->head = pNew;
    pQueue->end = pNew;
  }else{
    pQueue->end->pNext = pNew;
    pQueue->end = pNew;
    pNew->pNext = NULL;//calloc已经初始化为NULL不过这是好习惯，应该是
  }
  pQueue->size++;
  return 0;
}
int deQuene(queue_t *pQueue){
  if(pQueue->size == 0){
    return -1;
  }
  //正常情况
  node_t *p = pQueue->head;
  pQueue->head = p->pNext;

  if(pQueue->size == 1){
    pQueue->head = NULL;
    pQueue->end = NULL;
  }

  pQueue->size--;
  free(p);

return 0;
}


