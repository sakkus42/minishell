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
			break;
		t_token = t_token->next;
	}
	return (count);
}

t_cmnd	*new_node(int count_cmnd)
{
	t_cmnd	*t_res;

	t_res = malloc(sizeof(t_cmnd));
	printf("count_cmnd:	%d\n", count_cmnd);
	t_res->expand_cmnd = malloc(sizeof(char *) * (count_cmnd + 1));
	t_res->expand_cmnd[count_cmnd] = NULL;
	t_res->next = NULL;
	return (t_res);
}

int	is_input(char *c)
{
	if (ft_strchr(c, '>'))
		return (0);
	else
		return (1);
}

void	split_pipe(t_token *t_token, t_cmnd **t_cmd)
{
	t_cmnd	*t_tmp;
	int		i;

	while (t_token)
	{
		i = 0;
		if (t_token->if_pipe)
			t_token = t_token->next;
		if (!t_token->if_pipe && !t_token->if_red)
		{
			t_tmp = new_node(count_cmnd(t_token));
			t_tmp->is_input = -1;
		}
		else if (t_token->if_red)
		{
			t_tmp = new_node(count_cmnd(t_token));
			t_tmp->expand_cmnd[i++] = t_token->cmnd[0];
			t_tmp->is_input = is_input(t_token->cmnd[0]);
			t_token = t_token->next;
		}
		while (t_token && !t_token->if_pipe && !t_token->if_red)
		{
			t_tmp->expand_cmnd[i++] = t_token->cmnd[0];
			t_token = t_token->next;
		}
		ft_lstadd_back_t_cmnd(t_cmd, t_tmp);
	}
}

void	print_struct(t_token *t_token)
{
	while (t_token)
	{
		printf("%s\n", t_token->cmnd[0]);
		t_token = t_token->next;
	}
}

void	print_struct_cmnd(t_cmnd *t_cmnd)
{
	int i = 0;
	while (t_cmnd)
	{
		i = 0;
		while (t_cmnd->expand_cmnd[i])
			printf("%s ", t_cmnd->expand_cmnd[i++]);
		printf("\n");
		t_cmnd = t_cmnd->next;
	}
}

void	parser()
{
	g_data.pipe_count = 0;
	g_data.t_token = lexer();
	if (!g_data.t_token)
	{
		g_data.t_cmnd = NULL;
		return ;
	}
	split_pipe(g_data.t_token, &(g_data.t_cmnd));
	// print_struct_cmnd(g_data.t_cmnd);
}