#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("-----1\n");
	printf("-----2\n");
	printf("-----3\n");
	printf("-----4\n");
	pid_t pid = fork();
	if(pid > 0)
	{
		for(int i = 0; i < 100; i++)
		{
			 printf("我是父进程，pid = %d, 子进程pid = %d\n", getpid(), pid);
		}
	
	}
	else if(pid == 0)
	{
		for(int i = 0; i < 100; i++)
		{
			 printf("我是子进程，pid = %d, 父进程pid = %d\n", getpid(), getppid());
		}
	}	
	else
	{
		perror("fork失败");
	}
	return 0;
}


