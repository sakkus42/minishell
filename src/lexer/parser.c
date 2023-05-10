#include "lexer.h"

int	count_cmnd(t_token *t_token)
{
	int	count;

	count = 0;
	while (t_token)
	{
		if (!t_token->if_pipe && !t_token->if_red)
			count++;
		else
			break;
		t_token = t_token->next;
	}
	return (count);
}

t_cmnd	*new_node(int count_cmnd)
{
	t_cmnd	*t_res;

	t_res = malloc(sizeof(t_cmnd));
	printf("count_cmnd:	%d\n", count_cmnd + 1);
	t_res->expand_cmnd = malloc(sizeof(char *) * (count_cmnd + 1));
	t_res->expand_cmnd[count_cmnd] = NULL;
	t_res->next = NULL;
	return (t_res);
}

t_cmnd	*split_cmnd2(int *i, int *is, t_token *t_token)
{
	*i = 0;
	*is = 1;
	return (new_node(count_cmnd(t_token)));
}

void	split_cmnd(t_token *t_token, t_cmnd **t_cmd)
{
	int	is;
	int	i;
	t_cmnd	*t_tmp;

	is = 0;
	while (t_token)
	{
		if (!is)
			t_tmp = split_cmnd2(&i, &is, t_token);
		if (!t_token->if_pipe && !t_token->if_red)
			t_tmp->expand_cmnd[i++] = t_token->cmnd;
		else
		{
			t_tmp->operator = t_token->cmnd;
			ft_lstadd_back_t_cmnd(t_cmd, t_tmp);
			is = 0;
			i = 0;
		}
		t_token = t_token->next;
	}
	if (is)
	{
		t_tmp->operator = NULL;
		ft_lstadd_back_t_cmnd(t_cmd, t_tmp);
	}
}

void	parser()
{
	g_data.t_token = lexer();
	if (!g_data.t_token)
		return ;
	split_cmnd(g_data.t_token, &(g_data.t_cmnd));
}