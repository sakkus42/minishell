

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/minishell.h"

int toplam(int *x, int *y)
{
	int f = 10;
	x = &f;
	printf("toplam : %p\n",x);
	*x = 60;
	*y = 20;
	return *x+*y;
}

void	try(char *str)
{	
	str = malloc(1000);
}

int main()
{
	char *str;
	if (ft_strnstr("amk=sad", "amk=", 4))
		printf("ok\n");
}