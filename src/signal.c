#include "../include/minishell.h"

void	ctrl_d()
{
	write(1, "exit\n", 5);
	exit(0);
}

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\033[A");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	g_data.is = 1;
}

void signal_cntrl()
{
	struct termios term;

	signal(SIGINT, ctrl_c);
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
