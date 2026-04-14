#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
	printf("开启子进程\n");

	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid == 0)
	{
		//子进程中返回0， 进入子进程
		execlp("ls", "ls", "-l", NULL);

		perror("excelp error");
		exit(1);
	}
	else if(pid > 0)
	{
		sleep(1);
		printf("I'm parent: %d\n", getpid());
	}
	printf("都结束啦\n");
	return 0;
}
