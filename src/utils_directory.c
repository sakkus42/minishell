#include "../include/minishell.h"

//dosyanın ismini utils_directory yaprtım
int	find_dir(char *path, char *cmd)
{
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (ft_strncmp(dir->d_name, ".", ft_strlen(dir->d_name)) != 0 && ft_strncmp(dir->d_name, "..", ft_strlen(dir->d_name)) != 0) 
			{
				if (ft_strncmp(dir->d_name, cmd, ft_strlen(dir->d_name)) == 0)
					return (1);
			}
		}
		closedir(d);
	}
	return (0);
}