#include "head.h"

int pipeFd[2];
void func(int num){
  write(pipeFd[1],"1",1);//写,可让pipeFd[0]读就绪
}

int main(){
  pipe(pipeFd);
  signal(SIGINT, func);

  pool_t pool;
  initPool(&pool, 4);

  int socket_fd;
  initSocket(&socket_fd, "8080", "127.0.0.1");

  int epollFd = epoll_create1(0);
  epollAddFd(epollFd, socket_fd);
 
  epollAddFd(epollFd, pipeFd[0]);
  while(1){
    struct epoll_event ev[1024];
    int epollNum = epoll_wait(epollFd,ev, 1024, -1);

    for(int i = 0; i < epollNum; i++){
      int fd = ev[i].data.fd;
      if(fd == pipeFd[0]){

      }
      else if(fd == socket_fd){
        int net_fd = accept(socket_fd, NULL, NULL);
        
        pthread_mutex_lock(&pool.pool_lock);
        enQuene(&pool.queue, net_fd);
        pthread_cond_signal(&pool.cond);
        pthread_mutex_unlock(&pool.pool_lock);
      }
    }
  }

  return 0;
}
