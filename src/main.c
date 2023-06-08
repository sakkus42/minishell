#include "../include/minishell.h"

int main(int ac, char *arv[], char *envp[])
{
	(void)ac;
	(void)arv;
	
	g_data.paths = ft_split(getenv("PATH"), ':');
	// chdir(getenv("HOME"));
	init_program(envp);
	signal_cntrl();
	g_data.input = malloc(sizeof(char**));
	g_data.id = 0;
	g_data.executor_flag = 0;
	g_data.input_flag = 0;
	g_data.echo = -1;
	while (1)
	{
		g_data.input[0] = readline("minishell$ ");
		g_data.heredoc_flag = 0;
		if (!g_data.input[0] && !g_data.is)
			ctrl_d();
		if (!g_data.is && **g_data.input)
		{
			add_history(g_data.input[0]);
			parser();
			if (g_data.t_cmnd)
				exec_cmnd(g_data.t_cmnd);
			exit_free(0);
		}
		else
			exit_free(-1);
		g_data.is = 0;
	}
	return (0);
}