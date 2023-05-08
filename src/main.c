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
			char **str = lexer();
			int i = 0;
			while (str[i])
			{
				printf("%s\n", str[i]);
				free(str[i]);
				i++;
			}
			free(str);
			add_history(g_data.input);
		}
		exit_free(0);
		g_data.is = 0;
	}
	return (0);
}