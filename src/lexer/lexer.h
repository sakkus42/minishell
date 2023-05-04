#ifndef LEXER_H
#define LEXER_H

#include "../../include/minishell.h"

typedef struct s_lexer
{
	char		**token;
	char		*input;
	int			ERRFLAG;
	int			s_quo;
	int			d_quo;
	int			i;
	int			tmp;
	int			count_token;
	int			is;
}				t_lexer;

int	quo_count(int quo, char *input);

#endif