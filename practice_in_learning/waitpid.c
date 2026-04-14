#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>

int main()
{
	pid_t pid, wpid;
	int status;
	pid = fork();
	if(pid == 0)
	{
		printf("child:pid = %d, sleeping 5s\n", getpid());
		sleep(5);
		exit(23);
	}
	else if(pid > 0)
	{
		//非阻塞轮询
		while((wpid = waitpid(pid, &status, WNOHANG)) == 0)
		{
			printf("parent:child not done, doing other work...\n");
			sleep(1);
		}
		
		if(WIFEXITED(status))
		{
			printf("parent: child %d exited, code = %d\n", wpid, WEXITSTATUS(status));
		}
	}
	else
	{
		perror("fork");
		exit(1);
	}
	return 0;
}
