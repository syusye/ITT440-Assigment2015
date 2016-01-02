#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_BUF 100

main()
{
	int s1, s2, s3;
	struct sockaddr_in saddr;
	int ret, on=1;
	char outbuf[10];
	char inbuf[MAX_BUF+1];

	/* Create two stream sockets */

	s1 = socket( AF_INET, SOCK_STREAM, 0);
	s2 = socket( AF_INET, SOCK_STREAM, 0);

	/* Make s1 (the server) reusable form an address perspective.*/

	ret = setsockopt (s1, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	/* Create the address for the server socket */
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons (8192);
	saddr.sin_addr.s_addr = htonl( INADDR_ANY);

	/* Bind the  address to s1 */
	ret = bind( s1, (struct sockaddr_in *)&saddr, sizeof(saddr));

	/* Specify willingness to accept connections */
	ret = listen(s1,1);

	/* Make the client socket nonblocking */
	fcntl(s2, F_SETFL, O_NONBLOCK );

	/* Connect the two sockets together */
	ret = connect (s2, (struct sockaddr_in *)&saddr, sizeof(saddr));

	/* Allow the server to accept a new client socket */
	s3 = accept(s1, (struct sockaddr_in *) NULL, NULL);

	/* Generate some output data */
	outbuf[0] = 'a';
	outbuf[1] = 0 ;

	/* Make three distinct calls with the data */
	ret = write(s3, outbuf, 1);
	ret = write(s3, outbuf, 1);
	ret = write(s3, outbuf, 1);

	/* Sleep for one second */
	sleep(1);

	/* Read the data from the client */
	ret = read (s2, inbuf, MAX_BUF);

	/* Should have read 3 bytes */
	printf ("read %d bytes\n", ret);

	/* Close the sockets */
	close(s1);
	close(s2);
	close(s3);
}
