#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>

#define MAX_BUFFER 128
#define DAYTIME_SERVER_PORT 13


int main(void)
  {
   int serverFd, connectionFd;
   struct sockaddr_in servaddr;
   char timebuffer[MAX_BUFFER+1];
   time_t currentTime;

   serverFd = socket(AF_INET, SOCK_STREAM, 0);

   memset(servaddr.sin_zero, '\0', sizeof servaddr.sin_zero);
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
   servaddr.sin_port = htons(DAYTIME_SERVER_PORT);

   bind(serverFd, (struct sockaddr *) &servaddr, sizeof(servaddr));
   listen(serverFd, 5);

   while(1)
     {
      connectionFd = accept(serverFd, (struct sockaddr *) NULL, NULL);

      if(connectionFd >= 0)
        {
         currentTime = time(NULL);
         snprintf(timebuffer, MAX_BUFFER, "%s\n", ctime(&currentTIme));
         write(connectionFd, timebuffer, strlen(timebuffer));
         close(connectionFd);
        }
     }
   return 0; 
  }



