#include "../../include/minishell.h"

int built_in_ctl(char *str)
{
	if(ft_strcmp(str, "cd") == 0)
		return (1);
	else if(ft_strcmp(str, "echo") == 0)
		return (1);
	else if(ft_strcmp(str, "exit") == 0)
		return (1);
	else if(ft_strcmp(str, "pwd") == 0)
		return (1);
	else if(ft_strcmp(str, "clear") == 0)
		return (1);
	else if(ft_strcmp(str, "export") == 0)
		return (1);
	else if(ft_strcmp(str, "unset") == 0)
		return (1);
	else if(ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}
