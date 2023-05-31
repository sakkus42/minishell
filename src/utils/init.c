#include "../../include/minishell.h"

static void	init_env(char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
		i++;
	g_data.env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		g_data.env[i] = ft_strdup(envp[i]);
	g_data.env[i] = 0;
}

void	init_program(char **envp)
{
	getcwd(g_data.path, 4096);
	init_env(envp);
}