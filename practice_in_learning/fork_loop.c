#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int i;
	for(i = 0; i < 5; i++)
	{
		if(fork() == 0)
		{
			break;
		}
	}
	if(i == 5)
	{
		printf("I'm parent");
	}
	else
	{
		printf("I'm %dth child\n", i + 1);
	}
	return 0;
}
		
