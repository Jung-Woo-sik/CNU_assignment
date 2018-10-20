#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>

int main(int argc, char **argv)
{
    	int sockfd, clilen, n, downbyte, fd;
	char buf[1024];
	int state;

    	struct sockaddr_in serveraddr, clientaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (sockfd < 0)
	{
		perror("socket error : ");
		exit(0);
	}

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(1234);

	state = bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));

	if (state < 0)
	{	
		perror("bind error : ");
		exit(0);
	}

	fd = open("giga", O_CREAT|O_WRONLY|O_TRUNC, 0600);
	printf("fromTo is OK. sync conplete!\n");
	clilen = sizeof(clientaddr);
	n = recvfrom(sockfd, &buf, 1024, 0, (struct sockaddr *)&clientaddr, &clilen);

	while(n)
	{
		printf("%1ld of data received \n",n);
		write(fd, buf, n);
		downbyte += n;
		printf("recvfrom is ok. %d(current size)\n", downbyte);
		memset(buf, 0x00, 1024);
		n = recvfrom(sockfd, &buf, 1024, 0, (struct sockaddr *)&clientaddr, &clilen);
	}
	
	printf("Number of count : %1ld \n", downbyte);

    	close(sockfd);
}
