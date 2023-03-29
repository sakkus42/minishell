#include "../include/minishell.h"

// void	cmd_exec(void)
// {

// }

void	builtcmds(void)
{
	int	i;
	// if (ft_strncmp("echo", t_data.input, 5) == 0)
	// 	echo();
	// if (ft_strncmp("cd", t_data.input, 2) == 0)
	// 	cd();
	if (ft_strncmp("pwd", t_data.input, 3) == 0)
	{
		printf("%s\n", getenv("PWD"));
	}
	// if (ft_strncmp("export", t_data.input, 6) == 0)
	// 	export();
	// if (ft_strncmp("unset", t_data.input, 5) == 0)
	// 	unset();
	if (ft_strncmp("env", t_data.input, 3) == 0)
	{
		i = 0;
		while (t_data.env[i])
			printf("%s\n", t_data.env[i++]);
		
	}
	if (ft_strncmp("exit", t_data.input, 4) == 0)
	{
		printf("exit\n");
		exit_free();
	}
}
