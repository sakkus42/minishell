#include "../include/minishell.h"

struct input_parser
{
	char	**quote;
}parser;

int	is_blank_line(char *line)
{
	if (!*line)
		return (1);
	if (*line == ' ')
		return (is_blank_line(line + 1));
	else
		return (0);
}

void	input_parser(void)
{
	if (t_data.input[0] != '\'' && t_data.input[0] != '"')
		return ;
	parser.quote = ft_split(t_data.input, t_data.input[0]);
	t_data.inp_parser = malloc(sizeof(char **) * 999);
	int i = 0;
	if (parser.quote[i] && parser.quote[i + 1])
	{
		if (parser.quote[i + 1][0] != ' ')
			t_data.inp_parser[i] = ft_strjoin(parser.quote[i], parser.quote[i + 1]);
		else
		{
			i = 0;
			while (parser.quote[i])
			{
				if (is_blank_line(parser.quote[i]))
				{
					t_data.inp_parser[i] = ft_strdup(" ");
				}
				else
					t_data.inp_parser[i] = ft_strdup(parser.quote[i]);
				i++;
			}	
		}
	}
	else
	{
			t_data.inp_parser[i] = ft_strdup(parser.quote[i]);
			i++;
	}
	i = 0;
	while (t_data.inp_parser[i])
		printf("%s\n", t_data.inp_parser[i++]);
}