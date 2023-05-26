#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include <string.h>
#include "gnl/get_next_line_bonus.h"
  
int fd[4][2];

void	func(){
	static int i = 0;
	printf("fd[i][1]:	%d\n", fd[i][1]);
	int id = fork();
	if (id == 0){
		printf("selam\n");
		dup2(fd[i + 1][0], 1);
		i++;
		exit(1);
	}else{
		wait(&id);
		printf("fd[i][1]:	%d\n", fd[i][0]);
		char *str = get_next_line(fd[i][0]);
		printf("str:	%s\n", str);
		// ttyname(fd[i][0]) ? printf("ok\n") : printf("no\n");
		// isatty(fd[i][0]) ? printf("ok1\n") : printf("no1\n");
	}
}
int main()
{
	int i = 0;
	while (i < 3)
		pipe(fd[i++]);
	for (size_t i = 0; i < 4; i++)
	{
		func();
	}
	return (0);
}