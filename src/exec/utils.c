#include "exec.h"

int	is_executor(char **expand_cmd)
{
	if (expand_cmd[0][0] == '/')
		return (2);
	else if (expand_cmd[0][0] == '.' && expand_cmd[0][1] == '/')
		return (1);
	else
		return (0);
}

int	get_size_t_cmd(t_cmnd *t_cmd)
{
	if (!t_cmd)
		return (0);
	return (1 + get_size_t_cmd(t_cmd->next));
}

void	file_add(char **file, char **paths, t_cmnd *t_cmd)
{
	int	index;
	index = find_dir(paths, t_cmd->expand_cmnd_lower[0]);
	if (is_executor(t_cmd->expand_cmnd) == 1)
		index = find_dir(paths, t_cmd->expand_cmnd_lower[0] + 2);
	else if (is_executor(t_cmd->expand_cmnd) == 2 && \
			!access(t_cmd->expand_cmnd_lower[0], X_OK))
	{
		*file = ft_strdup(t_cmd->expand_cmnd_lower[0]);
		return ;
	}
	if (built_in_ctl(t_cmd->expand_cmnd_lower[0]))
	{
		printf("ok-builtin\n");
		*file = NULL;
		return ;
	}
	else if (index == -1 && is_executor(t_cmd->expand_cmnd))
	{
		printf("minishell: %s: No such file or directory\n",
			t_cmd->expand_cmnd[0]);
		g_data.exit_status = 127;
		*file = NULL;
		return ;
	}
	if (index != -1)
		*file = add_path(index, t_cmd->expand_cmnd_lower[0], paths);
	else
		*file = NULL;
}

int	is_directory(char *expand_cmnd)
{
	DIR	*d;

	d = opendir(expand_cmnd);
	if (d)
		closedir(d);
	return (d != NULL);
}

void	upper_to_lower(t_cmnd *t_cmd)
{
	int		i;
	int		k;

	while (t_cmd)
	{
		i = 0;
		k = 0;
		while (t_cmd->expand_cmnd_lower[i] && t_cmd->expand_cmnd_lower[i][k])
		{
			if (t_cmd->expand_cmnd_lower[i][k] >= 'A'
				&& t_cmd->expand_cmnd_lower[i][k] <= 'Z')
				t_cmd->expand_cmnd_lower[i][k] = t_cmd->expand_cmnd_lower[i][k]
					+ 32;
			if (t_cmd->expand_cmnd[i]
				&& t_cmd->expand_cmnd_lower[i][k + 1] == '\0')
			{
				i++;
				k = 0;
				continue ;
			}
			k++;
		}
		t_cmd = t_cmd->next;
	}
}
