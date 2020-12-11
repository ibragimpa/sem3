#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#define PORT 5051

int main(int argc, char const *argv[])
{
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};
  /* Создаем TCP сокет */
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;

}

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);




  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)  // строка -> в структуру сетевого адреса
  {
    printf("Not correct address");
    return -1;

  }

  if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("Connection failed\n");
    return -1;
  }




int pid = fork();
  if(pid != 0 )
  {
    while(1)
    {
      valread = read(sock, buffer, 1024);
      if(valread == 0) return 0;
      printf("%s", buffer);
      fflush(stdout);


      memset(buffer, 0, 1024);
    }

  }
  else
  {
    while(1)
    {
      fgets(buffer, 1023, stdin);
      send(sock, buffer, strlen(buffer), 0);
      memset(buffer, 0, 1024);
    }
  }


  printf("So long time coming!");
  return 0;
}
