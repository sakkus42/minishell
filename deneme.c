#include <stdio.h>
#include <stdlib.h>

struct s_try
{
	void	(*init)(struct s_try*);
	int i;
	int len;
	char *message;
} try1;

void	init(struct s_try *tr)
{
	tr->i = 0;
	tr->len = 0;
	tr->message = "hello struct oop";
}


int main(){
	struct s_try deneme;
	deneme.init = init;
	deneme.init(&deneme);
	printf("%s", deneme.message);
}