#include "../../include/minishell.h"

void	free_token(t_token *t_tok)
{
	t_token *t_tmp;

	while (t_tok)
	{
		t_tmp = t_tok->next;
		free(t_tok->cmnd[0]);
		free(t_tok->cmnd);
		free(t_tok);
		t_tok = t_tmp;
	}
	t_tok = 0;
}

void	exit_free(int is)
{
	int	i;
	t_cmnd *t_tmp;

	free_token(g_data.t_token);
	while (g_data.t_cmnd)
	{
		i = 0;
		// if (g_data.t_cmnd->cmnd_file)
		// 	free(g_data.t_cmnd->cmnd_file);
		// printf("ok\n");
		free(g_data.t_cmnd->expand_cmnd);
		t_tmp = g_data.t_cmnd->next;
		free(g_data.t_cmnd);
		g_data.t_cmnd = t_tmp;
	}
	g_data.t_cmnd = 0;
	if (g_data.input)
		free(g_data.input);
	if (is == 1)
		exit(1);
}