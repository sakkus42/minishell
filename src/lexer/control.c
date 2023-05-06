#include "lexer.h"

int	is_valid_quot(t_lexer *t_lex, char quot)
{
	if (t_lex->input[t_lex->i + 1] == quot && t_lex->input[t_lex->i + 2]
		&& !ft_strchr(" <>|", t_lex->input[t_lex->i + 2]))
	{
		t_lex->i += 2;
		return (0);	
	}
	if (t_lex->i > 0 && !ft_strchr(" <>|", t_lex->input[t_lex->i - 1]))
	{
		t_lex->i += 2;
		return (0);
	}
	return (1);
}

void	red_cntrl(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i + 1] && t_lex->input[t_lex->i] == t_lex->input[t_lex->i + 1])
		t_lex->i++;
	if (t_lex->i != 0 && ft_strchr("|>", t_lex->input[t_lex->i - 1]) && !is_great(t_lex))
	{
		printf("bash: syntax error near unexpected token '<'\n");
		t_lex->ERRFLAG = 1;
	}
	else if (!t_lex->input[t_lex->i + 1] || !skip_space(t_lex->input, &t_lex->i))
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		t_lex->ERRFLAG = 1;
	}
	else if (is_great(t_lex) && t_lex->input[t_lex->i + 1] == '>')
	{
		printf("bash: syntax error near unexpected token '>'\n");
		t_lex->ERRFLAG = 1;
	}
	else
	{
		t_lex->i++;
		t_lex->count_token++;
	}
}

void	pipe_cntrl(t_lexer *t_lex)
{
	if (t_lex->i == 0 || !t_lex->input[t_lex->i + 1])
		;
	else if (!t_lex->input[t_lex->i - 1])
		;
	else if (!skip_space(t_lex->input, &t_lex->i))
		;
	else
	{
		t_lex->i++;
		t_lex->count_token++;
		return ;
	}
	printf("bash: syntax error near unexpected token '|'\n");
	t_lex->ERRFLAG = 1;
}