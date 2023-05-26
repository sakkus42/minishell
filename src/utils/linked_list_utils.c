#include "../../include/minishell.h"

static t_token	*ft_lstlast(t_token *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static t_cmnd	*ft_lstlast_t_cmnd(t_cmnd *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}


void	ft_lstadd_back_t_cmnd(t_cmnd **lst, t_cmnd *new)
{
	t_cmnd	*last;

	last = ft_lstlast_t_cmnd(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

void	ft_print_struct(t_cmnd *t_cmd)
{
	int i;
	while (t_cmd)
	{
		i = 0;
		while (t_cmd->expand_cmnd[i])
			printf("%s ", t_cmd->expand_cmnd[i++]);
		printf("\n");
		t_cmd = t_cmd->next;
	}
}

