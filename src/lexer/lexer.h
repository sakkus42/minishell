#ifndef LEXER_H
#define LEXER_H

#include "../../include/minishell.h"

typedef struct s_lexer
{
	char		**token;
	char		*input;
	int			*len_array;
	int			ERRFLAG;
	int			FLAGPLUS;
	int			s_quo;
	int			d_quo;
	int			i;
	int			j;
	int			k;
	int			tmp;
	int			count_token;
}				t_lexer;

int	g_i;
int		is_great(t_lexer *t_lex);
int		quo_count(int quo, char *input);
int		is_valid_quot(t_lexer *t_lex, char quot);
int		*ft_intlcat(int len, int *src, int value);
char	skip_space(char *input, int *i);
void	reset_ver(t_lexer *t_lex);
void	skip_operator(t_lexer *t_lex);
void	skip_cmnd_arg(t_lexer *t_lex);
void	skip_quot(t_lexer *t_lex, char quot);
void	pipe_cntrl(t_lexer *t_lex);
void	red_cntrl(t_lexer *t_lex);


#endif