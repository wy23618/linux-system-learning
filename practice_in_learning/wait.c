#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if(pid == 0)
	{
		//子进程
		printf("---child:pid=%d, parent=%d, going to sleep 3s\n", getpid(), getppid());
		sleep(10);
		printf("----child die-Lose---------\n");
		exit(42);
	}
	else if(pid > 0)
	{
		//父进程
		printf("parent:pid=%d, waiting for child..\n", getpid());
		wpid = wait(&status);
		if(wpid == -1)
		{
			perror("wait error");
			exit(1);
		}
		if(WIFEXITED(status))//子进程正常终止
		{
			printf("child exit with %d\n", WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status))//子进程被信号终止
		{
			 printf("parent: child %d killed by signal %d\n",wpid, WTERMSIG(status));
		}
	}
	
		else
		{
			perror("fork");
			exit(1);
		}
	
	return 0;
	}
