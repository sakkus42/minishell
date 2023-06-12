#include "exec.h"

void	dup2_scale(t_cmnd *t_cmd)
{
	if (t_cmd->next && t_cmd->prev && t_cmd->next->input_fd == -1)
	{
		dup2(t_cmd->prev->fd[0], 0);
		dup2(t_cmd->fd[1], 1);
	}
	else if (t_cmd->next && t_cmd->next->input_fd == -1)
	{
		printf("ok1071\n");
		dup2(t_cmd->fd[1], 1);
	}
	else if (t_cmd->prev)
		dup2(t_cmd->prev->fd[0], 0);
	if (t_cmd->next && t_cmd->next->input_fd != -1)
		dup2(t_cmd->next->input_fd, 0);
}

void	close_all(t_cmnd *t_cmd)
{
	while (t_cmd->next)
	{
		close(t_cmd->fd[0]);
		close(t_cmd->fd[1]);
		t_cmd = t_cmd->next;
	}
}

void	close_unnecessary_fd(t_cmnd *t_cmd)
{
	if (t_cmd->next && t_cmd->prev)
	{
		close(t_cmd->prev->fd[0]);
		close(t_cmd->fd[1]);
	}
	else if (t_cmd->next)
		close(t_cmd->fd[1]);
	else if (t_cmd->prev)
		close(t_cmd->prev->fd[0]);
	if (t_cmd->next && t_cmd->next->input_fd != -1)
		close(t_cmd->next->input_fd);
}

void	wait_pid_all(t_cmnd *t_cmd)
{
	while (t_cmd)
	{
		waitpid(t_cmd->id, &(g_data.exit_status), 0);
		g_data.input_flag = 0;
		if (WIFEXITED(g_data.exit_status))
			g_data.exit_status = WEXITSTATUS(g_data.exit_status);
		t_cmd = t_cmd->next;
	}
	g_data.executor_flag = 0;
}
