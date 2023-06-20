/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:28:08 by sakkus            #+#    #+#             */
/*   Updated: 2023/06/15 15:28:10 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	get_paths(void)
{
	int		index;
	char	**path;

	if (g_data.paths)
	{
		index = 0;
		while (g_data.paths[index])
			free(g_data.paths[index++]);
		free(g_data.paths);
	}
	index = is_env("PATH");
	if (index == -1)
	{
		g_data.paths = NULL;
		return ;
	}
	path = ft_split(g_data.env[index], '=');
	g_data.paths = ft_split(path[1], ':');
	free(path[0]);
	free(path[1]);
	free(path);
}

int	get_size_t_cmd(t_cmnd *t_cmd)
{
	if (!t_cmd)
		return (0);
	return (1 + get_size_t_cmd(t_cmd->next));
}
