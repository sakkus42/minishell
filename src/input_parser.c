#include "../include/minishell.h"


struct input_parser
{
	char	*arg;
	int		i;
	int		j;
	int		k;
	int		quo_count;
	int		ARG_FLAG;
	char	quote;
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
	parser.i = 0;
	parser.j = 0;
	t_data.inp_parser = malloc(sizeof(char**) * 100);
	while(t_data.input[parser.i])
	{
		parser.k = 0;
		parser.ARG_FLAG = 0;
		parser.arg = malloc(sizeof(char) * 100);
		while(t_data.input[parser.i] == ' ')
			parser.i++;
		if (t_data.input[parser.i] == '"' || t_data.input[parser.i] == '\'')
		{
			parser.ARG_FLAG = 1;
			parser.quote = t_data.input[parser.i];
			parser.quo_count = 1;
			parser.i++;
		}
		while(t_data.input[parser.i])
		{
			if (!parser.ARG_FLAG && t_data.input[parser.i] == ' ')
			{
				parser.i++;
				break;
			}
			if (t_data.input[parser.i] == parser.quote)
			{
				parser.quo_count++;
				parser.i++;
				continue;
			}
			if (parser.ARG_FLAG && parser.quo_count % 2 == 0 && t_data.input[parser.i + 1] == ' ')
			{
				printf("quo_count %% 2:	%d\n", parser.quo_count % 2);
				parser.i++;
				break;
			}
			else
				parser.arg[parser.k++] = t_data.input[parser.i++];
		}
		parser.arg[parser.k] = 0;
		if (parser.k)
			t_data.inp_parser[parser.j++] = ft_strdup(parser.arg);
		// printf("parser.i:	%d\n", parser.i);
		free(parser.arg);
	}
	t_data.inp_parser[parser.j] = 0;
	int i = 0;
	while (t_data.inp_parser[i])
		printf("%s\n", t_data.inp_parser[i++]);
}