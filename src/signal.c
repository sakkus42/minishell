/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:28:45 by sakkus            #+#    #+#             */
/*   Updated: 2023/06/15 15:28:46 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_nl(void)
{
	printf("\033[A");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	g_data.is = 1;
}

void	ctrl_d(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (g_data.heredoc_flag)
		g_data.heredoc_flag = 0;
	if (ttyname(g_data.id) && !g_data.executor_flag && !g_data.input_flag)
		put_nl();
	g_data.exit_status = 1;
}

void	sighandler_quit(int sig)
{
	(void)sig;
	if (!g_data.input_flag)
		return ;
	else if (ttyname(g_data.id) && !g_data.executor_flag)
		printf("Quit: 3\n");
}

void	signal_cntrl(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, sighandler_quit);
}
