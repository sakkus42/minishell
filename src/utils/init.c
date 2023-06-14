#include "../../include/minishell.h"

static void	init_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_data.env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		g_data.env[i] = ft_strdup(envp[i]);
		i++;
	}
	g_data.env[i] = NULL;
}

void	init_program(char **envp)
{
	// chdir(getenv("HOME"));
	getcwd(g_data.path, 4096);
	init_env(envp);
	get_paths();
	g_data.input = malloc(sizeof(char **));
	g_data.id = 0;
	g_data.executor_flag = 0;
	g_data.input_flag = 0;
	g_data.echo = -1;
}
