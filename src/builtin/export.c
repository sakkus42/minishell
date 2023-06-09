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



int	first_ltter(char *str)
{
	int		i;

	if (str)
	{
		if ((!ft_isalpha(str[0]) && str[0] != '_') || str[0] == '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i = 1;
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
			{
				printf("minishell: export: `%s': not a valid identifier\n", str);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void	set_key_and_value(char **key, char **value, int *i)
{
	(*key) = ft_substr(g_data.env[*i], 0, ft_strchr(g_data.env[*i], '=')
			- (g_data.env[*i]));
	if (ft_strchr(g_data.env[*i], '='))
		(*value) = ft_substr(g_data.env[*i],
				ft_strlen(ft_strchr(g_data.env[*i], '=') + 250),
				ft_strlen(g_data.env[*i]));
	else
		(*value) = NULL;
}

void	print_export(void)
{
	char	**env;
	char	*s;

	env = g_data.env;
	while (*env)
	{
		s = ft_strchr(*env, '=');
		write(1, "declare -x ", 11);
		if (s)
		{
			write(1, *env, s - *env + 1);
			printf("%c%s", '"', s + 1);
			printf("%c\n", '"');
		}
		else
			printf("%s\n", *env);
		env++;
	}
}

void	do_export(char **str)
{
	int		i;
	char	*env_var;

	i = 1;
	env_var = str[1];
	if (str[1] == NULL)
		print_export();
	else
	{
		if (first_ltter(str[i]) && str)
			update_env(env_var, 1);
	}
}
