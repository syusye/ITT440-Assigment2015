#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void* thread_proc(void *argc);

int main( int argc, char *argv[])
{
	struct sockaddr_in saddr;
	int listensock;
	int newsock;
	int result;
	pthread_t thread_id;
	int val;

	listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	val = 1;

	result = setsockopt( listensock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	if( result< 0)
	{
		perror("Error setting socket option.");
		return 0;
	}

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(1972);
	saddr.sin_addr.s_addr = INADDR_ANY;

	result = bind(listensock, (struct sockaddr *) &saddr, sizeof(saddr));

	if(result<0)
	{
		perror("Error bind socket");
		return 0;
	}

	result = listen(listensock, 5);
	if(result<0)
	{
		perror("Error listen socket");
		return 0;
	}

	while(1)
	{
		newsock = accept(listensock, NULL, NULL);
		result = pthread_create(&thread_id, NULL, thread_proc, (void *) newsock);

		if(result!=0)
		{
			printf("Could not create thread.\n");
		}

		pthread_detach(thread_id);
		sched_yield();
	}
}

void* thread_proc(void *arg)
{
	int sock;
	char buffer[25];
	int nread;

	printf("child thread %i with pid %i created.\n", pthread_self(), getpid());

	sock = (int) arg;
	nread = recv( sock, buffer, 25, 0);
	buffer[nread] = '\0';
	printf("%s\n",buffer);
	send(sock, buffer, nread, 0);
	close(sock);

	printf("child thread %i with pid %i finished.\n", pthread_self(), getpid());
}
