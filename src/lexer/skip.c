#include "lexer.h"

void	skip_operator(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i] == '<' || t_lex->input[t_lex->i] == '>')
		red_cntrl(t_lex);
	if (t_lex->input[t_lex->i] == '|')
	{
		g_data.pipe_count++;
		pipe_cntrl(t_lex);
	}
}

void	skip_cmnd_arg(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i])
	{
		if (ft_strchr(" <>|", t_lex->input[t_lex->i]))
			break ;
		t_lex->i++;
	}
	t_lex->count_token++;
}

int	skip_space(char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
	if (input[*i] == '\0')
		return (0);
	return (1);
}

void	skip_quot(t_lexer *t_lex, char quot)
{
	if (!is_valid_quot(t_lex, t_lex->input[t_lex->i]))
		return ;
	t_lex->tmp = 1;
	while (t_lex->input[t_lex->i])
	{
		t_lex->i++;
		if ((t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
			&& t_lex->input[t_lex->i] != quot && !(t_lex->tmp % 2))
			t_lex->j++;
		if (t_lex->input[t_lex->i] == quot && (!t_lex->j || !(t_lex->j % 2)))
			t_lex->tmp++;
		if ((t_lex->input[t_lex->i] && t_lex->input[t_lex->i] == quot
			&& t_lex->input[t_lex->i + 1] && t_lex->input[t_lex->i + 1] == quot))
				continue;
		else if (ft_strchr("< >|", t_lex->input[t_lex->i]) && t_lex->tmp % 2 == 0)
			break;
		else if (t_lex->input[t_lex->i + 1] && !ft_strchr("< >|", t_lex->input[t_lex->i + 1]))
			continue;
		else if (t_lex->input[t_lex->i] && t_lex->input[t_lex->i] == quot
			&& t_lex->tmp % 2 == 0)
		{
			t_lex->i++;
			break;
		}
	}
	t_lex->count_token++;
}
