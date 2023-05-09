#include "../include/minishell.h"

//dosyanın ismini utils_directory yaprtım
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
					return (i);
			}
		}
		closedir(d);
		d = opendir(path[++i]);
	}
	
	return (0);
}