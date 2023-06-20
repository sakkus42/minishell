/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmnd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:28:24 by sakkus            #+#    #+#             */
/*   Updated: 2023/06/15 15:28:25 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
