#include "head.h"

int initSocket(int *socketFd, char *port, char *ip){
  *socketFd = socket(AF_INET, SOCK_STREAM, 0);

  //接触TIME_WAIT导致的端口占用问题
  int reuse = 1;
  setsockopt(*socketFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  struct in_addr inAddr;
  inet_aton(ip,&inAddr);
  int portNet = htons(atoi(port));
  
  struct sockaddr_in socketAddr;
  socketAddr.sin_family = AF_INET;
  socketAddr.sin_port = portNet;
  socketAddr.sin_addr = inAddr;
  
  int ret_bind = bind(*socketFd, (struct sockaddr*)&socketAddr, sizeof(socketAddr));
  ERROR_CHECK(ret_bind, -1, "bind");

  int ret_listen = listen(*socketFd, 10);
  return 0;
}
