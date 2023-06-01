#include "include/minishell.h"
int is = 1;
struct s{
	void (*try)(int);
}st;


void sign_handler1(int sig){
	(void)sig;
	printf("sign1\n");

}

void sign_handler2(int sig){
	(void)sig;
	printf("sign2\n");
	is = 0;
}

void	func1(){
	printf("hello\n");
}

void func2(){
	printf("world\n");
	signal(SIGINT, sign_handler2);
	while (is)
		;
	signal(SIGINT, st.try);
}

int main()
{
	st.try = sign_handler1;
	signal(SIGINT, st.try);
	func1();
	func2();
	while (1)
		;
}