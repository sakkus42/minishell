/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:54:06 by sakkus            #+#    #+#             */
/*   Updated: 2023/06/20 10:55:09 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_pip	*new_node(t_pip *prev)
{
	t_pip	*res;

	res = malloc(sizeof(t_pip));
	pipe(res->fd);
	res->prev = prev;
	res->next = NULL;
	return (res);
}

static t_pip	*ft_lstlast(t_pip *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static void	ft_lstadd_back_t_pip(t_pip **lst, t_pip *new)
{
	t_pip	*last;

	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

int	size_cntrl(t_pip *res)
{
	if (!res)
		return (0);
	return (1 + size_cntrl(res->next));
}

t_pip	*init_pipe(void)
{
	int		pipe_count;
	t_pip	*tmp;
	t_pip	*res;

	res = NULL;
	tmp = NULL;
	pipe_count = g_data.pipe_count + 1;
	while (pipe_count--)
	{
		tmp = new_node(tmp);
		ft_lstadd_back_t_pip(&res, tmp);
	}
	return (res);
}
