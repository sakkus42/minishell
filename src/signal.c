#include "../include/minishell.h"

void	ctrl_d(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	put_nl()
{
	printf("\033[A");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	g_data.is = 1;
}

void	ctrl_c()
{
	if (g_data.heredoc_flag)
		g_data.heredoc_flag = 0;
	if (ttyname(g_data.id) && !g_data.executor_flag && !g_data.input_flag)
		put_nl();
}

void	sighandler_quit(int sig)
{
	(void)sig;
	if (!g_data.input_flag)
		return;
	else if (ttyname(g_data.id) && !g_data.executor_flag)
		printf("Quit: 3\n");
}

void	signal_cntrl(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, sighandler_quit);
}