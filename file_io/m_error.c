#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	char buf[1024];
	int n;

	n = read(999, buf, 1024);
	if(n == -1)
	{
		perror("read错误：");
	}
	int fd = open("test.txt", O_RDONLY | O_CREAT, 644);
	if(fd == -1)
	{
		perror("open错误");
	}
	n = write(fd, "hello", 5);
	if(n == -1)
	{
		perror("write错误：");
	}
	close(fd);
	return 0;
}
