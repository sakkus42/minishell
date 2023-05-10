

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int toplam(int *x, int *y)
{
	int f = 10;
	x = &f;
	printf("toplam : %p\n",x);
	*x = 60;
	*y = 20;
	return *x+*y;
}


int main()
{
	printf("main : %p\n", string());
	system("leaks a.out");
}