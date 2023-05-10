#include "../include/minishell.h"

void	exit_free(int is)
{
	int	i;

	i = 0;
	while (g_data.t_cmnd)
	{
		free(g_data.t_cmnd);
		g_data.t_cmnd = g_data.t_cmnd->next;
	}
	if (g_data.input)
		free(g_data.input);
	if (is == 1)
		exit(1);
}

char	*add_path(int index)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(g_data.paths[index], "/");
	res = ft_strjoin(tmp, g_data.t_token->cmnd);
	return (res);
}

void	exxec()
{
	char *cmd = g_data.t_token->cmnd;
	int	is = find_dir(g_data.paths, cmd);
	if (!is)
	{
		printf("bash: %s: command not found\n", g_data.t_token->cmnd);
		return ;
	}
	g_data.t_token->cmnd_file = add_path(is);
	printf("%s\n", g_data.t_token->cmnd_file);
	int id = fork();
	if (id == 0)
	{
		is = 0;
		ft_print_struct(g_data.t_cmnd);
		execve(g_data.t_token->cmnd_file, g_data.t_cmnd->expand_cmnd, g_data.env);
		exit(1);
	}
	else
		wait(&id);
}

int main(int ac, char *arv[], char *envp[])
{
	(void)ac;
	(void)arv;
	
	g_data.paths = ft_split(getenv("PATH"), ':');
	g_data.env = envp;
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
			if (!g_data.t_token)
				continue;
			// t_token *t_iter = g_data.t_token;
			// while (t_iter)
			// {
			// 	printf("%s\n", t_iter->cmnd);
			// 	t_iter = t_iter->next;
			// }
			exxec();
		}
		exit_free(0);
		g_data.is = 0;
	}
	return (0);
}