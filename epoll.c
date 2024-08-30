#include "head.h"

int epollAddFd(int epoll_fd, int fd){
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events = EPOLLIN;
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);

  return 0;
}
