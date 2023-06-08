/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydegerli <ydegerli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:57:26 by ydegerli          #+#    #+#             */
/*   Updated: 2023/06/01 17:06:44 by ydegerli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_cd(char *dest, char *old_dir)
{
	char	*key;

	getcwd(g_data.path, 4096);
	if (!dest)
	{
		key = get_env("HOME");
		if (!key)
			printf("minishell : HOME not set\n");
		if (chdir(key) == -1)
			printf("çalişmadi\n");
		free(key);
	}
	else
	{	
		if (access(dest, X_OK) == 0)
			chdir(dest);
		else if (ENOENT == errno)
			printf("minishell: cd: %s: No such file or directory\n", dest);
	}
	update_env_pwds(old_dir);
	getcwd(g_data.path, 4096);
}
