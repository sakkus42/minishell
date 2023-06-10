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

int	is_invalid_arg(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i][0]) || (!ft_isalpha(str[i][0]) && str[i][0] == '_'))
			return (i);
		i++;
	}
	return (-1);
}

int	arg_counter(char **str)
{
	if (!str)
		return (0);
	return (1 + arg_counter(str + 1));
}

char *env_name(int i)
{
	char *env;

	if (ft_strchr(g_data.env[i], '='))
		env = ft_substr(g_data.env[i], 0, ft_strchr(g_data.env[i], '=') - g_data.env[i]); 
	else
		env = ft_strdup(g_data.env[i]);
	return (env);
}

int	is_env(char *str)
{
	int		i;
	char	*env;

	i = 0;
	while (g_data.env[i])
	{
		env = env_name(i);
		if (!ft_strcmp(env, str))
		{
			free(env);
			return (i);
		}
		free(env);
		i++;
	}
	return (-1);
}

void	ft_unset(char **str)
{
	char	**tmp;
	char	*env;
	int		i;
	int		k;

	if (is_invalid_arg(str) != -1)
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str[is_invalid_arg(str)]);
		return ;
	}
	if (is_env(str[1]) != -1)
		return ;
	printf("ok\n");
	tmp = malloc(sizeof(char *) * (size_env(g_data.env)));
	printf("g_Data.env size:	%d\n", size_env(g_data.env));
	i = 0;
	k = 0;
	while (g_data.env[i])
	{
		env = env_name(i);
		if (!ft_strcmp(env, str[1]))
		{
			i++;
			free(env);
			continue ;
		}
		free(env);
		tmp[k++] = ft_strdup(g_data.env[i++]);
	}
	printf("k: %d\n", k);
	tmp[k] = NULL;
	free_double_pointer(&g_data.env);
	g_data.env = tmp;
}
