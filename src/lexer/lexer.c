/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:28:26 by sakkus            #+#    #+#             */
/*   Updated: 2023/06/15 15:28:28 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	count_token(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i])
	{
		if (t_lex->errflag)
			break ;
		else if (t_lex->input[t_lex->i] == '\'' || \
				t_lex->input[t_lex->i] == '"')
			skip_quot(t_lex, t_lex->input[t_lex->i]);
		else if (!ft_strchr("<>| ", t_lex->input[t_lex->i]))
			skip_cmnd_arg(t_lex);
		else if (ft_strchr("<>|", t_lex->input[t_lex->i]))
			skip_operator(t_lex);
		else
			t_lex->i++;
	}
}

void	lex_sep(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i])
	{
		while (t_lex->input[t_lex->i] && t_lex->input[t_lex->i] == ' ')
			t_lex->i++;
		if (t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
			quot_add(t_lex);
		else if (t_lex->input[t_lex->i] && \
				ft_strchr("<>|", t_lex->input[t_lex->i]))
			operator_add(t_lex);
		else if (t_lex->input[t_lex->i] && \
				!ft_strchr("< >|", t_lex->input[t_lex->i]))
			cmnd_add(t_lex);
	}
	t_lex->token[t_lex->k] = NULL;
	return ;
}

t_token	*lexer(void)
{
	t_lexer	t_lex;

	t_lex.s_quo = quo_count('\'', g_data.input[0]);
	t_lex.d_quo = quo_count('"', g_data.input[0]);
	if (t_lex.s_quo % 2 != 0 || t_lex.d_quo % 2 != 0)
	{
		printf("missing quote\n");
		return (NULL);
	}
	t_lex.input = ft_strdup(g_data.input[0]);
	reset_ver(&t_lex);
	count_token(&t_lex);
	if (t_lex.errflag || !t_lex.count_token)
	{
		free(t_lex.input);
		free(t_lex.token);
		return (NULL);
	}
	t_lex.token = ft_calloc(sizeof(char *), t_lex.count_token + 1);
	reset_ver(&t_lex);
	t_lex.t_res = NULL;
	lex_sep(&t_lex);
	free(t_lex.input);
	free(t_lex.token);
	return (t_lex.t_res);
}
