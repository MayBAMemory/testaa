#include "head.h"

typedef struct train_s {
  int buf_size;
  char buf[60];
} train_t;

int sendBFile(int netFd) {
  char *fileName = "1.txt";
  int fileFd = open(fileName, O_RDWR);
  train_t train; 
  struct stat stat;
  fstat(fileFd, &stat);

  // 传输文件大小，实际上只是为了做进度条
  memset(&train, 0, sizeof(train));
  train.buf_size = stat.st_size;
  send(netFd, &train.buf_size,  sizeof(off_t), MSG_NOSIGNAL);

  memset(&train, 0, sizeof(train));
  train.buf_size = strlen(fileName);
  memcpy(train.buf, fileName, train.buf_size);

  // 发送文件名长度与文件名
  int ret_send = send(netFd, &train, sizeof(int) + train.buf_size, MSG_NOSIGNAL);

  sendfile(netFd, fileFd, 0, stat.st_size);
  printf("send over\n");

  close(fileFd);
  return 0;
}
