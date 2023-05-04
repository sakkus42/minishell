#include "../include/minishell.h"
typedef struct s_parser
{
	char	**comarg;
	int		noaa;
	int		noa;
} t_parser;

int	parser()
{
	g_data.lex_array = lexer();
	if (!g_data.lex_array)
		return (0);
	return (1);
}

void SimpleCommand(t_data *parser, char **arg)
{
	t_parser.noaa = 0;
	t_parser.noa = 0;
}