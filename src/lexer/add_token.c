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
void	next_to_quot(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i] && !ft_strchr("< \"'>|", t_lex->input[t_lex->i]))
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
}
void	quot_add(t_lexer *t_lex)
{
	quot_from_quot(t_lex);
	if ((t_lex->input[t_lex->i] && ft_strchr("< >|", t_lex->input[t_lex->i])) || !t_lex->input[t_lex->i])
	{
		linked_add(t_lex, '"');
		t_lex->k++;
		return ;
	}
	else
	{
		next_to_quot(t_lex);
		while (t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
			quot_from_quot(t_lex);
		next_to_quot(t_lex);
		linked_add(t_lex, '"');
		t_lex->k++;
	}
}

void	operator_add(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i] == '|')
	{
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		linked_add(t_lex, '|');
		t_lex->k++;
	}
	else if (is_great(t_lex) || !is_great(t_lex))
	{
		if (t_lex->input[t_lex->i + 1] == t_lex->input[t_lex->i])
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		linked_add(t_lex, '<');
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
	linked_add(t_lex, 0);
	t_lex->k++;
}

void	linked_add(t_lexer *t_lex, int is)
{
	t_token *t_tmp;

	t_tmp = malloc(sizeof(t_token));
	t_tmp->cmnd = t_lex->token[t_lex->k];
	if (is == '<' || is == '>')
		t_tmp->if_red = 1;
	else if (is == '"' || is == '\'')
		t_tmp->if_quot = 1;
	else if (is == '|')
		t_tmp->if_pipe = 1;
	t_tmp->next = NULL;
	// printf("%s\n", t_lex->t_res->cmnd);
	ft_lstadd_back(&(t_lex->t_res), t_tmp);
}