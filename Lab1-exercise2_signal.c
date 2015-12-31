#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig)
{
        if(sig == SIGINT)
                printf("This is a special signal handler for SIGINT");
        if(sig == SIGKILL)
                printf("This is a special signal handler for SIGKILL");
        if(sig == SIGHUP)
                printf("This is a special signal handler for SIGHUP");
        if(sig == SIGTERM)
                printf("This is a special signal handler for SIGTERM");

}

int main(void)
{

	//void sigint_handler(int sig); /*prototype*/
	char s[200];

	if (signal (SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("SIGINT ERROR");
		exit(1);
	}
	
	if (signal (SIGKILL, sigint_handler) == SIG_ERR)
	{
		perror("SIGKILL ERROR");
		exit(1);
	}
	if (signal (SIGHUP, sigint_handler) == SIG_ERR)
	{
		perror("SIGHUP ERROR");
		exit(1);
	}
	if (signal (SIGTERM, sigint_handler) == SIG_ERR)
	{
		perror("SIGTERM ERROR");
		exit(1);
	}

	printf("Enter a string:\n");

	if (gets(s)==NULL)
	{
		perror("gets");
	}
	else
	{
		printf("String input : \"%s\"\n", s);
	}

	//return 0;
	while(1)
		sleep(1);

	return 0;

}
