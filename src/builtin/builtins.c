/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydegerli <ydegerli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:56:21 by ydegerli          #+#    #+#             */
/*   Updated: 2023/06/09 14:11:17 by ydegerli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_env(char **str)
{
	int	i;

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

int	is_n(char *arg)
{
	int i;

	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
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
	while (arg[i])
	{
		if (arg[i][0] == '-' && arg[i][1] == 'n' && is_n(arg[i]))
		{
			i++;
			continue ;
		}
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		else if (arg[0][0] == '-' && arg[0][1] == 'n' && is_n(arg[0]))
			break ;
		else
		{
			printf("\n");
			break ;
		}
		i++;
	}
}

void	ft_builtins(char **cmnd, char **cmnd_upper)
{
	int		nbr;

	nbr = 0;
	if (ft_strcmp(cmnd[0], "echo") == 0)
		ft_echo(&cmnd[1]);
	else if (ft_strcmp(cmnd[0], "clear") == 0)
		printf("\e[1;1H\e[2J");
	else if (ft_strcmp(cmnd[0], "pwd") == 0)
		printf("%s\n", getcwd(g_data.path, 4096));
	else if (ft_strcmp(cmnd[0], "cd") == 0)
		ft_cd(cmnd[1], g_data.path);
	else if (ft_strcmp(cmnd[0], "env") == 0)
		print_env(g_data.env);
	else if (ft_strcmp(cmnd[0], "export") == 0)
		do_export(cmnd_upper);
	else if (ft_strcmp(cmnd[0], "unset") == 0)
		ft_unset(cmnd_upper);
	else if (ft_strcmp(cmnd[0], "exit") == 0)
	{
		printf("exit\n");
		if (cmnd[1])
		{
			nbr = getting_number_in_exit(cmnd[1]);
			if (nbr == 0)
				nbr = ft_atoi(cmnd[1]);
		}
		if (cmnd[1] && cmnd[2])
		{
			g_data.exit_status = 1;
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		exit(nbr);
	}
}
