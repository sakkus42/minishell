#include "builtin.h"

void	print_env(char **str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(str[i], '=') != NULL)
			printf("%s\n", str[i]);
	}
}


void	n_ctl(char **arg, int i)
{
	if (ft_strcmp(arg[0], "-n") == 1)
	{
		while (arg[i])
		{
			if (ft_strcmp(arg[i], "-n") == 1 || ft_strcmp(arg[i], " ") == 1)
				i++;
		}
	}
}

void	ft_echo(char **arg)
{
	int	i;

	i = 0;
	if (!arg[i])
	{
		printf("\n");
		return ;
	}
	while (ft_strcmp(arg[i], "-n") == 0)
		i++;
	if (!arg[i])
		return ;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (ft_strcmp(arg[0], "-n") != 0)
		printf("\n");
}

void	ft_builtins(char **cmnd)
{
	char *pwd;
	char *old_dir;

	old_dir = NULL;
	pwd = NULL;
	if (ft_strcmp(cmnd[0], "echo") == 0)
		ft_echo(&cmnd[1]);
	else if (ft_strcmp(cmnd[0], "clear") == 0)
		printf("\e[1;1H\e[2J");
	else if (ft_strcmp(cmnd[0], "pwd") == 0)
		printf("%s\n", getcwd(g_data.path, 4096));
	else if(ft_strcmp(cmnd[0], "cd") == 0)
			ft_cd(cmnd[1], g_data.path);
	else if(ft_strcmp(cmnd[0], "env") == 0)
			print_env(g_data.env);
	else if(ft_strcmp(cmnd[0], "export") == 0)
			do_export(cmnd);
	else if(ft_strcmp(cmnd[0], "unset") == 0)
		ft_unset(g_data.env, cmnd[1]);
	else if(ft_strcmp(cmnd[0], "exit") == 0)
			exit(0);
}
