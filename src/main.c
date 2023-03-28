#include "../lib/minishell.h"

int is = 0;

void ctrl_c(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	is = 1;
}

void signal_cntrl()
{
	struct termios term;

	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main(int ac, char *arv[], char *envp[])
{
	t_data m_data;

	(void)ac;
	(void)arv;
	(void)envp;
	m_data.paths = ft_split(getenv("PATH"), ':');
	
	signal_cntrl();
	while (1)
	{
		m_data.input = readline("minishell$ ");
		if (m_data.input == NULL)
		{
			printf("\rminishell$ exit");
			exit(1);
		}
		if (is != 1)
			add_history(m_data.input);
		is = 0;
	}
	return (0);
}