#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd1 = dup(1);
	int fd2 = open("out.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if(fd2 == -1)
	{
		perror("open error");
		exit(1);
	}
	int fdret = dup2(fd2, 1);
	close(fd2);
	printf("line1\nline2\nline3\n");
	fflush(stdout);
	fdret = dup2(fd1, 1);
	close(fd1);
	printf("back to screen");
	return 0;
}

	

