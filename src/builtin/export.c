/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydegerli <ydegerli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:57:05 by ydegerli          #+#    #+#             */
/*   Updated: 2023/06/09 14:42:33 by ydegerli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		size_env(char **env)
{
	int	res;

	res = 0;
	while (env[res])
		res++;
	return (res);
}

int	repeat_index(char *env_name, char *cmd)
{
	char 	*env;
	int		i;

	i = 0;
	while (g_data.env[i])
	{
		if (ft_strchr(g_data.env[i], '='))
			env = ft_substr(g_data.env[i], 0, ft_strchr(g_data.env[i], '=') - g_data.env[i]); 
		else
			env = ft_strdup(g_data.env[i]);
		if (!ft_strcmp(env, env_name))
		{
			free(env);
			if ((ft_strchr(g_data.env[i], '=') && ft_strchr(cmd, '='))
					|| !ft_strchr(g_data.env[i], '='))
				return (i);
			else
				return (-2);
		}
		free(env);
		i++;
	}
	return (-1);
}

int size_expand_len(char *cmd)
{
	int		res;
	char	*env_name;

	if (ft_strchr(cmd, '='))
		env_name = ft_substr(cmd, 0, ft_strchr(cmd, '=') - cmd);
	else
		env_name = ft_strdup(cmd);
	res = repeat_index(env_name, cmd);
	free(env_name);
	return (res);
}

void	add_env_new(char *cmd)
{
	char	**tmp;
	int		len;
	int		i;
	int		repeat_index;

	len = size_env(g_data.env);
	repeat_index = size_expand_len(cmd);
	printf("len: %d\n", len);
	if (repeat_index == -1)
		tmp = malloc(sizeof(char *) * (len + 2));
	else if (repeat_index == -2)
		return ;
	else
	{
		free (g_data.env[repeat_index]);
		g_data.env[repeat_index] = ft_strdup(cmd);
		return ;
	}
	i = 0;
	while (g_data.env[i])
	{
		tmp[i] = ft_strdup(g_data.env[i]);
		i++;
	}
	tmp[i++] = ft_strdup(cmd);
	tmp[i] = NULL;
	printf("ok1\n");
	free_double_pointer(&g_data.env);
	printf("ok2\n");
	g_data.env = tmp;
}

void	print_export(char *str)
{
	int		i;
	int		k;
	char	*is;

	i = 0;
	k = 0;
	while (g_data.env[i])
	{
		is = ft_strchr(g_data.env[i], '=');
		k = 0;
		printf("%s", str);
		while (g_data.env[i][k])
		{
			if (k != 0 && g_data.env[i][k - 1] == '=' && str && is)
				printf("\"");
			printf("%c", g_data.env[i][k]);
			if (!g_data.env[i][k + 1] && str && is)
				printf("\"");
			k++;
		}
		if (g_data.env[i][k - 1] == '=')
				printf("\"");
		printf("\n");
		i++;
	}
	
}

void	do_export(char **cmnds)
{
	int	i;
	
	printf("is_invalid_arg:	%d\n", is_invalid_arg(cmnds));
	if (is_invalid_arg(cmnds) != -1)
	{
		printf("minishell: export: `%s': not a valid identifier\n", cmnds[is_invalid_arg(cmnds)]);
		return ;
	}
	if (!cmnds[1])
		print_export("declare -x ");
	else
	{
		i = 1;
		while (cmnds[i])
			add_env_new(cmnds[i++]);
	}
}
