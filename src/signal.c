#include "../include/minishell.h"

void	ctrl_d()
{

	exit_free(1);
}

void	ctrl_c(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	t_data.is = 1;
}

void signal_cntrl()
{
	struct termios term;

	signal(SIGINT, ctrl_c);
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
