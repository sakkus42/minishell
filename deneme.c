#include <stdio.h>
#include <stdlib.h>

struct s_try
{
	void	(*try)(int);
} try1;

void	add(int i){
	printf("hello world");
}

int main(){
	try1.try = add;
	try1.try(2);
}