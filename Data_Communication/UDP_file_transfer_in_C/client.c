#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <string.h>

long filesize (char *name) {
	int size;
	int flag;
	struct stat buf;
	flag = stat (name, &buf);
	if (flag == -1) return -1;
	size = buf.st_size;
	return (size);
}

int main(int argc, char **argv)
{
	int sockfd, n, cur_size = 0, tsize, tflag, len, fd;
    	char buf[1024];
	char fileName[50];
	float percent;

	struct sockaddr_in serveraddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("52.64.49.247");
	serveraddr.sin_port = htons(1234);
	
	printf("Enter file name >> ");
	scanf("%s", &fileName);
	fd = open(fileName, O_RDONLY);
	printf("sendTo is ok. sync complete!!\n");

	tsize = filesize(fileName);
	len = read(fd, buf, 1024);

	printf("sendTo is ok. send file desc complete\n");
	while(len)
	{
		n = sendto(sockfd, buf, len, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
		cur_size += n;
		percent =((float)cur_size / (float)tsize) * 100;
		printf("sendTo is ok. %d / %d(current size / total size), %.2f%\n ", cur_size, tsize, percent); 
		bzero(buf, 1024);
		len = read(fd, buf, 1024);
	}
	printf("sendTo is ok.fin complete!!\n");
    	printf("%d bytes/sec %dbyte/%dbyte %.0f%% processed.\n", tsize, cur_size, tsize, percent);

	close(sockfd);
}
