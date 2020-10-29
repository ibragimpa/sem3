#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int f1, f2;
    char *send_buf = "Hello";
    char recv_buf[128] = {0};
    int stat = 0;
    int id = getpid();
    scanf("%d", &stat);
    if (mkfifo("mk.fifo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1 && errno != EEXIST)
        error(0, errno, "mkfifo() error");
        if (mkfifo("mk2.fifo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1 && errno != EEXIST)
        error(0, errno, "mkfifo() error");

    f1 = open("mk.fifo", O_RDWR);
    f2 = open("mk2.fifo", O_RDWR);
    int f, fz = 0;
    //f2 = open("mk.fifo", O_RDWR);
    if (f1 == -1 )
        printf("Open error 1");
        if (f2 == -1 )
            printf("Open error 2");

  if(stat > 0)
      {
        f = f1;
        fz = f2;
      }
      else
      {
        f = f2;
        fz = f1;
      }
      while(1)
      {
        fork();
        if(getpid() == id)
        {
          char* str = malloc(sizeof(char)*100);
          fgets(str, 100, stdin);
          if (write(f, str, strlen(str)) == -1)
              printf("Can't write");
              free(str);
        }
        else
        {
          if (read(fz, recv_buf, sizeof(recv_buf) - 1) == -1)
          printf("Can't read");
          printf("New message by second: '%s'\n", recv_buf);
        }

      }
close(f1);
close(f2);
    return 0;
}
