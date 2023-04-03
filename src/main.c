#include "../include/minishell.h"

void ctrl_c(int sig)
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

void	exit_free(void)
{
	int	i;

	i = 0;
	while (t_data.paths[i])
		free(t_data.paths[i++]);
	if (t_data.input)
		free(t_data.input);
	// system("leaks minishell");
	exit(1);
}

int main(int ac, char *arv[], char *envp[])
{
	(void)ac;
	(void)arv;
	t_data.paths = ft_split(getenv("PATH"), ':');
	t_data.env = envp;
	signal_cntrl();
	while (1)
	{
		t_data.input = readline("minishell$ ");
		if (t_data.input == NULL)
		{
			printf("\rminishell$ exit\n");
			exit_free();
		}
		input_parser();
		builtcmds();
		if (t_data.is != 1)
			add_history(t_data.input);
		free(t_data.input);
		t_data.is = 0;
	}
	return (0);
}