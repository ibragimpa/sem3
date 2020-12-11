#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>

#define PORT 5051
#define MAX_NUMBER_SOCKETS 10

int sockets[MAX_NUMBER_SOCKETS] = {0};

void send_msg_to_chat(int senderSocket, char* s)
{
printf("Member %d wrote: %s\n", senderSocket, s);


  for(size_t i = 0; i < MAX_NUMBER_SOCKETS; i++){
    if(sockets[i] != -1 && sockets[i] != senderSocket)
    {
      send(sockets[i], s, strlen(s), 0);
    }
  }
}

void* threads_chat(void* socketArg)
{
  const int buffer_size = 1024;
int socket = *((int*)socketArg);
  send_msg_to_chat(socket, "\nSmd joined\n");
  free(socketArg);
  char buffer[1024] = {0};
  while(1)
  {

    int readVal = read(socket, buffer, buffer_size); // читаем в буфер



    if(readVal == 0 || strcmp(buffer, "exit") == 0) break;
    send_msg_to_chat(socket, buffer);
    memset(buffer, 0, buffer_size);
    }
    for(size_t i = 0; i < MAX_NUMBER_SOCKETS; i++)
    {
      if(sockets[i] == socket) sockets[i] = -1;
    }
    send_msg_to_chat(socket, "Smbd exit\n");
    return NULL;
}



int main(int argc, char const *argv[])
{


  for( size_t i = 0; i < MAX_NUMBER_SOCKETS; i++)
  {
    sockets[i] = -1;
  }
  int desc_server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);

 /* Создаем TCP сокет */
  desc_server_fd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(desc_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons( PORT );
  //создает сокет
  bind(desc_server_fd, (struct sockaddr *)&address, sizeof(address));

  listen(desc_server_fd, MAX_NUMBER_SOCKETS);  // установка макс колва участников
  while(1)
  {printf("OK\n");

    int desc_socket = accept(desc_server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen); // создание сокета
    int pos = -1;
  //  printf("OK\n");

  for(size_t i = 0; i < MAX_NUMBER_SOCKETS; i++)
  {printf("OK1\n");

    if(sockets[i] == -1)
    {
      pos = i;
      break;
    }
    printf("OK2\n");

  }

  sockets[pos] = desc_socket;
  int* socketPointer = (int*)malloc(sizeof(int));
  *socketPointer = desc_socket;
  pthread_t desc_thr;
  pthread_create(&desc_thr, NULL, threads_chat, socketPointer);
  puts("Smd joined.\n");
}
return 0;

}
