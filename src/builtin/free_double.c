/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydegerli <ydegerli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:57:57 by ydegerli          #+#    #+#             */
/*   Updated: 2023/06/01 17:17:27 by ydegerli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	free_double_pointer(char ***str)
{
	int	i;

	i = 0;
	if ((*str) == NULL)
		return ;
	while ((*str)[i])
		free((*str)[i++]);
	free((*str)[i]);
	free(*str);
}
