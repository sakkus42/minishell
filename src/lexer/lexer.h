#ifndef LEXER_H
# define LEXER_H

# include "../../include/minishell.h"

typedef struct s_lexer
{
	char		**token;
	t_token		*t_res;
	char		*input;
	int			errflag;
	int			s_quo;
	int			d_quo;
	int			i;
	int			j;
	int			k;
	int			tmp;
	int			count_token;
}				t_lexer;

int		is_great(t_lexer *t_lex);
int		quo_count(int quo, char *input);
int		is_valid_quot(t_lexer *t_lex, char quot);
int		skip_space(char *input, int *i);
int		*ft_intlcat(int len, int *src, int value);
int		count_cmnd(t_token *t_token);
char	*ft_str_cat(char *dest, char src);
void	reset_ver(t_lexer *t_lex);
void	skip_operator(t_lexer *t_lex);
void	skip_cmnd_arg(t_lexer *t_lex);
void	skip_quot(t_lexer *t_lex, char quot);
void	pipe_cntrl(t_lexer *t_lex);
void	red_cntrl(t_lexer *t_lex);
void	quot_from_quot(t_lexer *t_lex);
void	add_dolar(t_lexer *t_lex);
void	quot_add(t_lexer *t_lex);
void	operator_add(t_lexer *t_lex);
void	cmnd_add(t_lexer *t_lex);
void	linked_add(t_lexer *t_lex, int is);
void	add_dolar(t_lexer *t_lex);

#endif