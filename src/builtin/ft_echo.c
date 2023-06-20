/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:30:03 by sakkus            #+#    #+#             */
/*   Updated: 2023/06/15 15:30:06 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_n(char *arg)
{
	int	i;

	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	is_finish(char **arg, int i)
{
	printf("%s", arg[i]);
	if (arg[i + 1] != NULL)
		printf(" ");
	else if (arg[0][0] == '-' && arg[0][1] == 'n' && is_n(arg[0]))
		return (1);
	else
	{
		printf("\n");
		return (1);
	}
	return (0);
}

void	ft_echo(char **arg)
{
	int	i;
	int	is;

	i = 0;
	is = 0;
	if (!arg[i])
	{
		printf("\n");
		return ;
	}
	while (arg[i])
	{
		if (arg[i][0] == '-' && arg[i][1] == 'n' && is_n(arg[i]) && !is)
		{
			i++;
			continue ;
		}
		is = 1;
		if (is_finish(arg, i))
			break ;
		i++;
	}
}
