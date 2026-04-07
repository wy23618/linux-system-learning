#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>

void copy_file(char *src, char *dst)
{
	int fd1 = open(src, O_RDONLY);
	if(fd1 == -1) { perror("open1 error"); exit(1);}

	struct stat st;
	int ret = stat(src, &st);
	if(ret == -1) { perror("stat1 error"); exit(1);}

	int fd2 = open(dst, O_WRONLY|O_CREAT|O_TRUNC, st.st_mode);
	if(fd2 == -1) { perror("open2 error"); exit(1);}

	char buf[1024];
	ssize_t n;
	while((n = read(fd1, buf, sizeof(buf))) > 0)
	{
		write(fd2, buf, n);
	}
	close(fd1); close(fd2);	
}
void copy_dir(const char *src, const char *dst)
{
	DIR *sd;
	sd = opendir(src);
	if(sd == NULL) {printf("opendir error"); exit(1);}
	
	struct stat st;
	int ret = stat(src, &st);
	if(ret == -1) {perror("stat2 error"); exit(1);}
	mkdir(dst, st.st_mode);

	struct dirent *sdp;
	while((sdp = readdir(sd)) != NULL)
	{
		if(strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name,  "..") == 0) continue;
		char src_path[1024];
		char dst_path[1024];
		sprintf(src_path, "%s/%s", src, sdp->d_name);
		sprintf(dst_path, "%s/%s", dst, sdp->d_name);

		struct stat st2;
		lstat(src_path, &st2);

		if(S_ISREG(st2.st_mode))
		{
			copy_file(src_path, dst_path);
		}
		else if(S_ISDIR(st2.st_mode))
		{
			copy_dir(src_path, dst_path);
		}
		else if(S_ISLNK(st2.st_mode))
		{
			char link_buf[1024];
			ssize_t len = readlink(src_path, link_buf, sizeof(link_buf) - 1);
			link_buf[len] = '\0';//readlink末尾不会自动加0，因为在这里我们把buf当成字符串用了，C中字符串必须以\0结尾；
			symlink(link_buf, dst_path);
		}

	}
	closedir(sd);
}
int main(int argc, char * argv[]) 
{
	if(argc < 3)
	{
		printf("请传入源目录和目标目录\n");
		return 0;
	}
	copy_dir(argv[1], argv[2]);
	return 0;
}

