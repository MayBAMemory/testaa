#include "head.h"

int pipeFd[2];
void func(int num) {
  write(pipeFd[1], "1", 1); // 写,可让pipeFd[0]读就绪
}

int main() {
  pipe(pipeFd);
  if (fork() != 0) { // 父进程
//alskdjkasldjaskljdklj
    //askdaskldnklasnkldasnkln
    signal(2, func);
    wait(NULL);
    printf("子进程已退出\n");
    exit(0);
  }
  // 子进程
  setpgid(0, 0);
  pool_t pool;
  initPool(&pool, 4);

  //int socket_fd;
  //initSocket(&socket_fd, "8080", "127.0.0.1");

  int epollFd = epoll_create1(0);
  //epollAddFd(epollFd, socket_fd);

  epollAddFd(epollFd, pipeFd[0]);
  while (1) {
    struct epoll_event ev[10];
    int epollNum = epoll_wait(epollFd, ev, 10, -1);
     if (epollNum == -1) {
        if (errno == EINTR) {
            // 被信号中断，继续等待
            continue;
        } else {
            // 打印错误信息
            perror("epoll_wait error");
            exit(EXIT_FAILURE);
        }
    }
    printf("%d\n",epollNum);
    for (int i = 0; i < epollNum; i++) {
      int fd = ev[i].data.fd;
      // 新连接
    /*  if (fd == socket_fd) {
        printf("new connect\n");
        int net_fd = accept(socket_fd, NULL, NULL);

        pthread_mutex_lock(&pool.pool_lock);
        enQuene(&pool.queue, net_fd);

        pthread_cond_signal(&pool.cond);
        pthread_mutex_unlock(&pool.pool_lock);
      }
*/
      // SIGINT触发捕捉
      if (fd == pipeFd[0]) {
        printf("捕捉到信号\n");

        char buf[60] = {0};
        read(pipeFd[0], buf, sizeof(buf));

        pthread_mutex_lock(&pool.pool_lock);
        pool.exitFlag = 1;
        pthread_cond_broadcast(&pool.cond);
        pthread_mutex_unlock(&pool.pool_lock);

        for (int k = 0; k < pool.threadNum; k++) {
          pthread_join(pool.threadIds[k], NULL);
          printf("ok\n");
        }
        printf("子线程清理完毕\n");
        close(pipeFd[0]);
        close(epollFd);
        exit(0);
      }
    }
  }
  close(pipeFd[0]);
  //close(socket_fd);
  return 0;
}
