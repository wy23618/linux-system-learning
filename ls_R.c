#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>

#define PATH_LEN 256

void fetchdir(const char *dir, void (*fcn)(char *));
void isfile(char *name);

void isfile(char *name)
{
	struct stat sb;
	//先获取文件属性
	if(lstat(name, &sb) < 0)
	{
		perror("lstat error");
		return;
	}
	//不是目录就打印文件名
	if(!S_ISDIR(sb.st_mode))
	{
		printf("%s\n", name);
		return;
	}
	//是目录就调fetchdir递归
	fetchdir(name, isfile);
}
void fetchdir(const char *dir, void(*fcn)(char *))
{
	char path[PATH_LEN];
	DIR *dp;
	struct dirent *sdp;
	//先打开目录
	dp = opendir(dir);
	if (dp == NULL)
	{
		perror("opendir error");
		return;
	}
	while((sdp = readdir(dp)) != NULL)
	{
		//先跳过.   .. 
		if(strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0) continue;
		//接下来要拼接完整路径
		sprintf(path, "%s/%s", dir, sdp->d_name);
		//调用isfile(fcn)
		fcn(path);
	}
	closedir(dp);
}


int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("usage: %s <dir>\n", argv[0]);
		exit(1);
	}
	isfile(argv[1]);
	return 0;
}
