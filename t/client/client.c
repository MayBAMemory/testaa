#include <my_header.h>

void progress_bar(double hundred) {
  int barWidth = 70;
  int pos = barWidth * (hundred / 100.0);
  char bar[barWidth + 1];
  memset(bar, ' ', sizeof(bar)); // 初始化填充空格
  for (int i = 0; i < pos; ++i) {
    bar[i] = '='; // 填充已完成部分
  }
  if (pos < barWidth) {
    bar[pos] = '>'; // 当前进度指示器
  }
  bar[barWidth] = '\0'; // 确保字符串结束符

  printf("\033[0;34m[%s] [%.0f%%]\033[0m\r", bar, hundred); // 输出进度条
  fflush(stdout); // 确保输出实时刷新
}

int getFile(int netFd) {

  int name_len; 

  //接受文件长度
  off_t file_size = 0; 
  recv(netFd, &file_size, sizeof(off_t), 0);
  printf("file_size %ld\n",file_size);

  // 接收文件名长度
  recv(netFd, &name_len, sizeof(int), MSG_WAITALL);
  printf("name_len: %d\n",name_len);

  char bufName[60] = {0};
  // 接收文件名
  recv(netFd, bufName, name_len, MSG_WAITALL);
  printf("bufName %s\n",bufName);



  int file_fd = open(bufName, O_WRONLY | O_CREAT | O_TRUNC, 0666);

  off_t curSize = 0;
  off_t lastSize = 0;

  // 接收文件内容
  char buf[8192];
  while (curSize < file_size) {

    ssize_t bytes_recv = recv(netFd, buf, sizeof(buf), MSG_WAITALL);
    if (bytes_recv <= 0) {
      break;
    }

    write(file_fd, buf, bytes_recv);

    curSize += bytes_recv;
    double percentage = (double)curSize * 100 / file_size;

    if (percentage - (double)lastSize * 100 / file_size >= 1 ||curSize == file_size) {
      lastSize = curSize;
      if (curSize == file_size) {
        percentage = 100.0;
      }
        progress_bar(percentage);
    }
  }
  close(file_fd);
  printf("\n");
  return 0;
}

int main() {
  char *ip = "127.0.0.1";
  char *port = "8080";

  int socketFd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(atoi(port));

  int ret_connect = connect(socketFd, (struct sockaddr *)&addr, sizeof(addr));
  ERROR_CHECK(ret_connect, -1, "connect");

  getFile(socketFd);
  close(socketFd);
  return 0;
}
