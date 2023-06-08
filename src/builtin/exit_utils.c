#include "builtin.h"

int	getting_number_in_exit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
		{
			printf("exit %s: numberic argument required\n", str);
			return (255);
		}
		i++;
	}
	return (0);
}
