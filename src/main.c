#include "../include/minishell.h"

int	main(int ac, char *arv[], char *envp[])
{
	(void)ac;
	(void)arv;
	init_program(envp);
	signal_cntrl();
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
