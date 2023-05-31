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
}

void	exit_free(int is)
{
	int	i;
	t_cmnd *t_tmp;
	
	if (is != -1)
	{
		free_token(g_data.t_token);
		while (g_data.t_cmnd)
		{
			i = 0;
			free(g_data.t_cmnd->expand_cmnd);
			t_tmp = g_data.t_cmnd->next;
			free(g_data.t_cmnd);
			g_data.t_cmnd = t_tmp;
		}
	}
	if (g_data.input)
		free(g_data.input);
	if (is == 1)
		exit(1);
}