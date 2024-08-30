#include "head.h"

int epollAddFd(int epoll_fd, int fd){
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;

    int ret_epoll_ctl = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");

    return 0;
}
