#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	pid_t pid = fork();
	if(pid > 0)
	{
		printf("父进程 pid = %d, 我不回收子进程\n", getpid());
		while(1); sleep(1);
	}
	else if(pid == 0)
	{
		printf("子进程 pid = %d, 我先走了\n", getpid());
		exit(0);
	}
	return 0;
}
