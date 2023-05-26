#include "exec.h"

int	get_size_t_cmd(t_cmnd *t_cmd)
{
	if (!t_cmd)
		return (0);
	return (1 + get_size_t_cmd(t_cmd->next));
}

void	dup2_scale(t_cmnd *t_cmd)
{
	if (t_cmd->next)
	{
		printf("no run\n");
		dup2(t_cmd->next->fd[0], STDOUT_FILENO);
	}
	if (t_cmd->prev)
	{
		printf("run\n");
		dup2(STDIN_FILENO, t_cmd->fd[0]);
	}
	
}

void	close_all(t_cmnd *t_cmd)
{
	while (t_cmd)
	{
		close(t_cmd->fd[0]);
		close(t_cmd->fd[1]);
		t_cmd = t_cmd->next;
	}
}

void	execve_run(t_cmnd *t_cmd)
{
	int		id;
	int		index;
	char	*file;

	index = find_dir(g_data.paths, t_cmd->expand_cmnd[0]);
	if (index == -1)
	{
		printf("minishell: %s: command not found\n", t_cmd->expand_cmnd[0]);
		return ;
	}
	file = add_path(index, t_cmd->expand_cmnd[0]);
	id = fork();
	if (id == 0)
	{
		dup2_scale(t_cmd);
		close_all(t_cmd);
		execve(file, t_cmd->expand_cmnd, g_data.env);
		exit(1);
	}
	else
		wait(&id);
	free(file);
}


void	exec_cmnd(t_cmnd *t_cmd)
{
	if (!g_data.pipe_count && get_size_t_cmd(g_data.t_cmnd) == 1)
	{
		printf("first\n");
		execve_run(g_data.t_cmnd);
		return ;
	}
	while (t_cmd)
	{
		int id;
		if (t_cmd->is_input == 2)
			execve_run(t_cmd);
		t_cmd = t_cmd->next;
	}
}