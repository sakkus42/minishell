#include "lexer.h"

void	add_dolar(t_lexer *t_lex)
{
	// bunun devamı yazılacak
	if (t_lex->input[t_lex->i + 1] && t_lex->input[t_lex->i + 1] == '?')
	{
		t_lex->i += 2;
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], '0');
		return ;
	}
}

void	quot_add(t_lexer *t_lex)
{
	quot_from_quot(t_lex);
	if ((t_lex->input[t_lex->i] && ft_strchr("< >|", t_lex->input[t_lex->i])) || !t_lex->input[t_lex->i])
	{
		t_lex->k++;
		return ;
	}
	else
	{
		while (t_lex->input[t_lex->i] && !ft_strchr("< \"'>|", t_lex->input[t_lex->i]))
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		while (t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
		{
			quot_from_quot(t_lex);
		}
		t_lex->k++;
	}
}

void	operator_add(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i] == '|')
	{
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->k++;
	}
	else if (is_great(t_lex) || !is_great(t_lex))
	{
		if (t_lex->input[t_lex->i + 1] == t_lex->input[t_lex->i])
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->k++;
	}
}

void	cmnd_add(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i] && t_lex->input[t_lex->i] != ' '
		&& !ft_strchr("< >|", t_lex->input[t_lex->i]))
	{
		while (t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
		{
			t_lex->tmp = t_lex->input[t_lex->i];
			quot_from_quot(t_lex);
		}
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
	}
	t_lex->k++;
}
