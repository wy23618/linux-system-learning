#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int i;
	pid_t pid, wpid;
	pid_t target_pid = 0;

	for(i = 0; i < 5; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			break;
		}
		if(i == 2)
		{
			target_pid = pid;//第三个子进程的pid
		}
	}
	if(i == 5)
	{
		//父进程，只等第三个子进程
		printf("parent:waiting for child %d (the 3rd one)\n", target_pid);
		wpid = waitpid(target_pid, NULL, 0);
		printf("parent:child %d reclaimed\n", wpid);
	}
	else
	{
		sleep(i);
		printf("I'm %dth child, pid=%d\n", i + 1, getpid());
	}
	return 0;
}
