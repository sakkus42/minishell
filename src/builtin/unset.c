/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydegerli <ydegerli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:57:20 by ydegerli          #+#    #+#             */
/*   Updated: 2023/06/01 17:19:18 by ydegerli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*new_str(char *str, char *news)
{
	int	j;
	int	x;

	x = 1;
	j = 0;
	news = malloc(sizeof(char) * (ft_strlen(str)));
	while (str[x])
		news[j++] = str[x++];
	free(news);
	return (news);
}

int	ft_chrcmp(char c1, char c2)
{
	if (c1 == c2)
		return (1);
	return (0);
}

void	ft_unset(char **env, char *str)
{
	int		i;
	char	dollar;
	char	*new;

	if (!str)
		return ;
	i = 0;
	(void)env;
	dollar = '$';
	new = NULL;
	new = new_str(str, new);
	if (ft_chrcmp(dollar, str[0]))
	{
		while (env[i])
		{
			if (ft_strcmp(new, env[i]) == 0)
				update_env(env[i], -1);
			i++;
		}
	}
}
