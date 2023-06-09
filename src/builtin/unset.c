/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydegerli <ydegerli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:57:20 by ydegerli          #+#    #+#             */
/*   Updated: 2023/06/09 13:18:59 by ydegerli         ###   ########.fr       */
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

void	ft_unset(char **str)
{
	update_env(*str, -1);
}
