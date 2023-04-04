#include "../include/minishell.h"

void	exit_free(int is)
{
	int	i;

	i = 0;
	if (t_data.inp_parser && !is && *t_data.input)
	{
		while (t_data.inp_parser[i])
			free(t_data.inp_parser[i++]);
		free(t_data.inp_parser);
	}
	if (t_data.input && is != 1)
		free(t_data.input);
	if (is == 1)
	{
		// system("leaks minishell");
		exit(1);
	}
}

int main(int ac, char *arv[], char *envp[])
{
	(void)ac;
	(void)arv;
	char	*home;

	home = getenv("HOME");
	chdir(home);
	t_data.paths = ft_split(getenv("PATH"), ':');
	t_data.env = envp;
	signal_cntrl();
	while (1)
	{
		t_data.input = readline("minishell$ ");
		if (!t_data.input)
			ctrl_d();
		if (!t_data.is && *t_data.input)
		{
			input_parser();
			builtcmds();
			add_history(t_data.input);
		}
		exit_free(0);
		t_data.is = 0;
	}
	return (0);
}