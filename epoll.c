#include "head.h"

int epollAddFd(int epoll_fd, int fd){
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = fd;
  int ret_epoll_ctl = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);

  return 0;
}
