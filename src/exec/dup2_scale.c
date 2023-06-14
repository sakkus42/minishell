#include "exec.h"

t_cmnd	*end_cmnd(int is_input, t_cmnd *t_cmd, int context)
{
	t_cmnd	*res;

	res = NULL;
	while (t_cmd->next && t_cmd->next->context == context)
	{
		if (t_cmd->next->is_input == is_input)
			res = t_cmd->next;
		t_cmd = t_cmd->next;
	}
	return (res);
}

t_cmnd	*start_end_cmnd(int is_input, t_cmnd *t_cmd, int context)
{
	t_cmnd	*res;

	res = NULL;
	while (t_cmd->prev && t_cmd->prev->context == context)
	{
		if (t_cmd->prev->is_input == is_input)
			return(t_cmd->prev);
		t_cmd = t_cmd->prev;
	}
	return (res);
}

void	redirection_scale(t_cmnd *t_cmd)
{
	t_cmnd	*tmp_output;
	t_cmnd	*tmp_input;
	
	tmp_output = end_cmnd(0, t_cmd, t_cmd->context);
	tmp_input = end_cmnd(1, t_cmd, t_cmd->context);
	if (tmp_output)
	{
		printf("okasdsa123\n");
		dup2(tmp_output->fd[1], 1);
	}
	else if (t_cmd->prev && t_cmd->prev->is_input == 0)
	{
		tmp_output = start_end_cmnd(0, t_cmd, t_cmd->context);
		dup2(tmp_output->fd[1], 1);
	}
	if (tmp_input)
	{
		printf("oks34\n");
		dup2(tmp_input->fd[0], 0);
	}
	else if (t_cmd->prev && t_cmd->prev->is_input == 1)
	{
		printf("oks35\n");
		tmp_input = start_end_cmnd(1, t_cmd, t_cmd->context);
		dup2(tmp_input->fd[0], 0);
	}
	
}

void	dup2_scale(t_cmnd *t_cmd)
{
	if (t_cmd->next && t_cmd->prev
		&& t_cmd->next->is_input == 2
			&& t_cmd->prev->is_input == 2)
	{
		dup2(t_cmd->prev->fd[0], 0);
		dup2(t_cmd->fd[1], 1);
	}
	else if (t_cmd->next && t_cmd->next->is_input == 2)
		dup2(t_cmd->fd[1], 1);
	else if (t_cmd->prev && t_cmd->prev->is_input == 2)
		dup2(t_cmd->prev->fd[0], 0);
	redirection_scale(t_cmd);
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
	t_cmnd	*tmp;

	if (t_cmd->next && t_cmd->prev)
	{
		close(t_cmd->prev->fd[0]);
		close(t_cmd->fd[1]);
	}
	else if (t_cmd->next && t_cmd->next->is_input == 2)
		close(t_cmd->fd[1]);
	else if (t_cmd->prev && t_cmd->prev->is_input == 2)
		close(t_cmd->prev->fd[0]);
	if (t_cmd->next && t_cmd->next->is_input == 1 && t_cmd->context == t_cmd->next->context)
	{
		tmp = end_cmnd(1, t_cmd, t_cmd->context);
		close(tmp->fd[0]);
	}
	else if (t_cmd->next && t_cmd->next->is_input == 0 && t_cmd->context == t_cmd->next->context)
	{
		tmp = end_cmnd(0, t_cmd, t_cmd->context);
		close(tmp->fd[1]);
	}
	if (t_cmd->prev && t_cmd->prev->is_input == 1 && t_cmd->context == t_cmd->prev->context)
		close(t_cmd->prev->fd[0]);
	else if (t_cmd->prev && t_cmd->prev->is_input == 0 && t_cmd->context == t_cmd->prev->context)
		close(t_cmd->prev->fd[1]);
}

void	wait_pid_all(t_cmnd *t_cmd)
{
	while (t_cmd)
	{
		waitpid(t_cmd->id, &(g_data.exit_status), 0);
		g_data.input_flag = 0;
		if (WIFEXITED(g_data.exit_status))
			g_data.exit_status = WEXITSTATUS(g_data.exit_status);
		if (g_data.exit_status == 127 && t_cmd->is_input == 2 && !g_data.executor_flag)
			printf("minishell: %s: command not found\n", t_cmd->expand_cmnd[0]);
		t_cmd = t_cmd->next;
	}
	g_data.executor_flag = 0;
}
