#include "lexer.h"

int	quo_count(int quo, char *input)
{
	int	i;
	int	count;
	int	is;

	i = 0;
	count = 0;
	is = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && input[i] != quo && !count)
			is = input[i];
		else if (input[i] == is)
			is = 0;
		if (input[i] == quo && !is)
			count++;
		i++;
	}
	return (count);
}

void	reset_ver(t_lexer *t_lex)
{
	t_lex->i = 0;
	t_lex->j = 0;
	t_lex->k = 0;
	t_lex->tmp = 0;
	t_lex->count_token = 0;
	t_lex->ERRFLAG = 0;
	t_lex->FLAGPLUS = 0;
}

int	is_great(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i] == '>')
		return (1);
	if (t_lex->input[t_lex->i] == '<')
		return (0);
	return (-1);
}
