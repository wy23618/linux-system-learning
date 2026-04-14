#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int main(void)
{
	int fd;
	fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd < 0)
	{
		perror("open error");
		exit(1);
	}

	dup2(fd, STDOUT_FILENO);
	execlp("ps", "ps", "ax", NULL);
	perror("excelp error");
	return 0;
}
