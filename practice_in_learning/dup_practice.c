#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int fd = open("a.text", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (fd == -1)
       	{
	       	perror("open");
	       	exit(1);
	}
	int fd2 = dup(fd);
	if(fd2 == -1)
	{
		perror("dup");
		exit(1);
	}
	printf("fd = %d, fd2 = %d\n", fd, fd2);

	ssize_t n = write(fd, "hello", 5);
	if(n == -1)
	{
		printf("write1 error");
		exit(1);
	}
	n = write(fd2, "world", 5);
	lseek(fd, 0, SEEK_SET);
	if(n == -1)
	{
		printf("write2 error");
		exit(1);
	}
	char buf[1024];
	while((n = read(fd, buf, sizeof(buf))) > 0)
	{
		write(STDOUT_FILENO, buf, n);
	}
	if(n == -1)
	{
		perror("read error");
		exit(1);
	}
	close(fd);
	close(fd2);
	return 0;
}	
