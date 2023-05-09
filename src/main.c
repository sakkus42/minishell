#include "../include/minishell.h"

void	exit_free(int is)
{
	int	i;

	i = 0;
	if (g_data.inp_parser && !is && *g_data.input)
	{
		while (g_data.inp_parser[i])
		{
			free(g_data.inp_parser[i++]);
		}
		free(g_data.inp_parser);
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
	char *arg[] = {g_data.t_token->cmnd, NULL};
	printf("%s\n", g_data.t_token->cmnd_file);
	int id = fork();
	if (id == 0)
	{
		execve(g_data.t_token->cmnd_file, arg, g_data.env);
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
			g_data.t_token = lexer();
			t_token *t_iter = g_data.t_token;
			if (!g_data.t_token)
				continue;
			while (t_iter)
			{
				printf("%s\n", t_iter->cmnd);
				t_iter = t_iter->next;
			}
			exxec();
		}
		exit_free(0);
		g_data.is = 0;
	}
	return (0);
}