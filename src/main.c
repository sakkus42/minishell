#include "../include/minishell.h"

void	run_comand()
{
	int	is;

	is = find_dir(g_data.paths, g_data.t_cmnd->expand_cmnd[0]);
	if (is == -1)
	{
		printf("bash: %s: command not found\n", g_data.t_cmnd->expand_cmnd[0]);
		g_data.t_cmnd->cmnd_file = NULL;
	}
	else
	{
		g_data.t_cmnd->cmnd_file = add_path(is);
		int id = fork();
		if (id == 0)
		{
			is = 0;
			execve(g_data.t_cmnd->cmnd_file, g_data.t_cmnd->expand_cmnd, g_data.env);
			exit(1);
		}
		else
			wait(&id);
	}
}

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
			run_comand();
		}
		exit_free(0);
		g_data.is = 0;
	}
	return (0);
}