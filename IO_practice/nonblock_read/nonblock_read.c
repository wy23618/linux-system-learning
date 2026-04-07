#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
int main()
{
	int flag = fcntl(STDIN_FILENO, F_GETFL);
	if(flag < 0){perror("fcntl error"); exit(1);}
	flag |= O_NONBLOCK;
	flag = fcntl(STDIN_FILENO, F_SETFL, flag);
	if(flag < 0){perror("fcntl error"); exit(1);}
	char buf[1024];
	ssize_t n;
	while(1)
	{
		n = read(STDIN_FILENO, buf, sizeof(buf));
		if(n > 0)
		{
			write(STDOUT_FILENO, buf, n);
		}
		else if(n == -1 && errno == EAGAIN)
		{
			printf("------\n");
			sleep(2);
		}
		else if(n == 0)
		{
			break;
		}
	}


	return 0;
}



