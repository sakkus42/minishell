#include "../../include/minishell.h"

t_token	*ft_lstlast(t_token *lst)
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