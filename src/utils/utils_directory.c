#include "../../include/minishell.h"

int	find_dir(char **path, char *cmd)
{
	DIR *d;
	struct dirent *dir;
	int	i;
	
	i = 0;
	d = opendir(path[i]);
	while (d)
	{
		while ((dir = readdir(d)) != NULL) {
			if (ft_strncmp(dir->d_name, ".", ft_strlen(dir->d_name)) != 0 && ft_strncmp(dir->d_name, "..", ft_strlen(dir->d_name)) != 0) 
			{
				if (!ft_strncmp(dir->d_name, cmd, ft_strlen(cmd)) && ft_strlen(cmd) == ft_strlen(dir->d_name))
				{
					closedir(d);
					return (i);
				}
			}
		}
		closedir(d);
		d = opendir(path[++i]);
	}
	free(d);
	free(dir);
	return (-1);
}

char	*add_path(int index, char *cmnd, char **paths)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(paths[index], "/");
	res = ft_strjoin(tmp, cmnd);
	free(tmp);
	return (res);
}

void	upper_to_lower(t_cmnd *t_cmd)
{
	int		i;
	int		k;

	while (t_cmd)
	{
		i = 0;
		k = 0;
		while(t_cmd->expand_cmnd_lower[i] && t_cmd->expand_cmnd_lower[i][k])
		{
			if (t_cmd->expand_cmnd_lower[i][k] >= 'A' && t_cmd->expand_cmnd_lower[i][k] <= 'Z')
				t_cmd->expand_cmnd_lower[i][k] = t_cmd->expand_cmnd_lower[i][k] + 32;
			if (t_cmd->expand_cmnd[i] && t_cmd->expand_cmnd_lower[i][k + 1] == '\0')
			{
				i++;
				k = 0;
				continue;
			}
			k++;
		}
		t_cmd = t_cmd->next;
	}
}