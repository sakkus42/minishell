#include "lexer.h"

static void	add_dolar2(t_lexer *t_lex);

static void	add_env_value(t_lexer *t_lex, char *env_name)
{
	char	*env_value;
	int		i;
	char	**hay;

	i = 0;
	env_value = 0;
	while (g_data.env[i])
	{
		hay = ft_split(g_data.env[i], '=');
		if(ft_strnstr(hay[0], env_name, ft_strlen(env_name)))
			env_value = ft_strdup(hay[1]);
		free(hay[0]);
		free(hay[1]);
		free(hay);
		if (env_value)
			printf("env value:%s\n", env_value);
		if (env_value)
			break;
		i++;
	}
	if (!env_value)
		return ;
	i = 0;
	while (env_value[i])
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], env_value[i++]);
	free(env_value);
}

void	add_dolar(t_lexer *t_lex)
{
	char	*tmp;
	char	*exit_status;

	if (t_lex->input[t_lex->i + 1] && t_lex->input[t_lex->i + 1] == '?')
	{
		t_lex->i += 2;
		exit_status = ft_itoa(g_data.exit_status);
		tmp = exit_status;
		while (*tmp)
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], *tmp++);
		free(exit_status);
	}
	else if (!t_lex->input[t_lex->i + 1])
		return ;
	else
		add_dolar2(t_lex);
}

void	add_dolar2(t_lexer *t_lex)
{
	int		i;
	int		count;
	char	*env_name;

	i = t_lex->i + 1;
	count = 0;
	while (t_lex->input[i] && !ft_strchr(" |<>\"'", t_lex->input[i]))
	{
		count++;
		i++;
	}
	env_name = malloc(sizeof(char) * (count + 1));
	env_name[count] = '\0';
	i = t_lex->i + 1;
	count = 0;
	while (t_lex->input[i] && !ft_strchr(" |<>\"'", t_lex->input[i]))
		env_name[count++] = t_lex->input[i++];
	t_lex->i = i;
	add_env_value(t_lex, env_name);
	free(env_name);
}