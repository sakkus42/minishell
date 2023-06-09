#include "lexer.h"

int	count_cmnd(t_token *t_token)
{
	int	count;

	count = 0;
	if (t_token->if_red)
	{
		t_token = t_token->next;
		count++;
	}
	while (t_token)
	{
		if (!t_token->if_pipe && !t_token->if_red)
			count++;
		else
			break ;
		t_token = t_token->next;
	}
	return (count);
}

t_cmnd	*new_node(int count_cmnd, t_cmnd *t_prev)
{
	t_cmnd	*t_res;

	t_res = malloc(sizeof(t_cmnd));
	t_res->expand_cmnd = malloc(sizeof(char *) * (count_cmnd + 1));
	t_res->expand_cmnd_lower = malloc(sizeof(char *) * (count_cmnd + 1));
	t_res->expand_cmnd[count_cmnd] = NULL;
	t_res->expand_cmnd_lower[count_cmnd] = NULL;
	t_res->input_fd = -1;
	t_res->id = -1;
	pipe(t_res->fd);
	t_res->next = NULL;
	t_res->prev = t_prev;
	return (t_res);
}

int	is_input(char *c)
{
	if (ft_strchr(c, '>'))
		return (0);
	else if (ft_strchr(c, '<'))
		return (1);
	return (2);
}

t_token	*split_pipe2(t_token *t_token, t_cmnd *t_tmp, int i)
{
	while (t_token && !t_token->if_pipe && !t_token->if_red)
	{
		t_tmp->expand_cmnd[i] = t_token->cmnd[0];
		t_tmp->expand_cmnd_lower[i++] = ft_strdup(t_token->cmnd[0]);
		t_token = t_token->next;
	}
	return (t_token);
}

void	split_pipe(t_token *t_token, t_cmnd **t_cmd)
{
	t_cmnd	*t_tmp;
	int		i;

	t_tmp = NULL;
	while (t_token)
	{
		i = 0;
		if (t_token->if_pipe)
			t_token = t_token->next;
		if (!t_token->if_pipe && !t_token->if_red)
		{
			t_tmp = new_node(count_cmnd(t_token), t_tmp);
			t_tmp->is_input = 2;
		}
		else if (t_token->if_red)
		{
			t_tmp = new_node(count_cmnd(t_token), t_tmp);
			t_tmp->expand_cmnd[i] = t_token->cmnd[0];
			t_tmp->expand_cmnd_lower[i++] = ft_strdup(t_token->cmnd[0]);
			t_tmp->is_input = is_input(t_token->cmnd[0]);
			t_token = t_token->next;
		}
		t_token = split_pipe2(t_token, t_tmp, i);
		ft_lstadd_back_t_cmnd(t_cmd, t_tmp);
	}
}

void	parser(void)
{
	g_data.pipe_count = 0;
	g_data.t_token = lexer();
	if (!g_data.t_token)
	{
		g_data.t_cmnd = NULL;
		return ;
	}
	split_pipe(g_data.t_token, &(g_data.t_cmnd));
	upper_to_lower(g_data.t_cmnd);
	ft_print_struct(g_data.t_cmnd);
}
