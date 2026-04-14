#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
	int fd = open("link.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if(fd == -1)
	{
		perror("open error");
		exit(1);
	}
	ssize_t n;
	char buf[1024];
	while((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
	{
		write(fd, buf, n);
	}
	close(fd);
	int ret = link("link.txt", "new_link.txt");
	if(ret == -1)
	{
		perror("link error");
		exit(1);
	}
	struct stat st;
	ret = stat("link.txt", &st);
	printf("link.txt 的inode是：%lu\n", st.st_ino);
	ret = stat("new_link.txt", &st);
	printf("new_link.txt的inlde是：%lu\n", st.st_ino);
	ret = rename("new_link.txt", "new_new_link.txt");
	if(ret == -1) {perror("rename error"); exit(1);}
	ret = truncate("new_new_link.txt", 10);
	if(ret == -1) {perror("truncate error"); exit(1);}
	ret = symlink("new_new_link.txt", "D.txt");
	if(ret == -1){perror("symlink error"); exit(1);}
	char buf2[1024];
	ssize_t s =  readlink("D.txt", buf2, sizeof(buf2));
	if(s == -1){perror("readlink error"); exit(1);}
	printf("D.txt 指向：");
	fflush(stdout);
	write(STDOUT_FILENO, buf2, s);
	write(STDOUT_FILENO, "\n", 1);
	unlink("new_new_link.txt");
	unlink("D.txt");
	return 0;
}

