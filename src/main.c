#include "../include/minishell.h"



int main(int ac, char *arv[], char *envp[])
{
	(void)ac;
	(void)arv;
	
	g_data.paths = ft_split(getenv("PATH"), ':');
	g_data.env = envp;
	chdir(getenv("HOME"));
	signal_cntrl();
	while (1)
	{
		g_data.input = readline("minishell$ ");
		g_data.LEXFLAG = 0;
		if (!g_data.input)
			ctrl_d();  
		if (!g_data.is && *g_data.input)
		{
			add_history(g_data.input);
			parser();
			if (!g_data.t_cmnd)
				continue;
			exec_cmnd(g_data.t_cmnd);
		}
		exit_free(0);
		g_data.is = 0;
	}
	return (0);
}