/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:28:42 by sakkus            #+#    #+#             */
/*   Updated: 2023/06/20 13:06:49 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cntrl_arg(int ac, char **arv)
{
	if (ac > 1)
	{
		printf("Invalid Argument: %s\n", arv[0]);
		exit(127);
	}
}

int	main(int ac, char *arv[], char *envp[])
{
	cntrl_arg(ac, arv);
	init_program(envp);
	signal_cntrl();
	while (1)
	{
		g_data.input[0] = readline("minishell$ ");
		g_data.heredoc_flag = 0;
		if (!g_data.input[0] && !g_data.is)
			ctrl_d();
		if (!g_data.is && **g_data.input)
		{
			add_history(g_data.input[0]);
			parser();
			if (g_data.t_cmnd)
				exec(g_data.t_cmnd);
			exit_free(0);
		}
		else
			exit_free(-1);
		g_data.is = 0;
	}
	return (0);
}
