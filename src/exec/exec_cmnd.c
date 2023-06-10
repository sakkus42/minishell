#include "exec.h"

void	execve_run2(t_cmnd *t_cmd)
{
	ft_builtins(t_cmd->expand_cmnd_lower, t_cmd->expand_cmnd);
	g_data.exit_status = 0;
}

void	execve_run(t_cmnd *t_cmd, char **paths)
{
	char	*file;

	if (built_in_ctl(t_cmd->expand_cmnd_lower[0]) && get_size_t_cmd(t_cmd) == 1)
	{
		execve_run2(t_cmd);
		return ;
	}
	file_add(&file, paths, t_cmd);
	t_cmd->id = fork();
	if (t_cmd->id == 0)
	{
		dup2_scale(t_cmd);
		close_all(g_data.t_cmnd);
		close(t_cmd->fd[0]);
		close(t_cmd->fd[1]);
		if (built_in_ctl(t_cmd->expand_cmnd_lower[0]))
			ft_builtins(t_cmd->expand_cmnd_lower, t_cmd->expand_cmnd);
		else if (execve(file, t_cmd->expand_cmnd, g_data.env) == -1 && \
				!is_executor(t_cmd->expand_cmnd))
			printf("minishell: %s: command not found\n", t_cmd->expand_cmnd[0]);
		exit(0);
	}
	close_unnecessary_fd(t_cmd);
	g_data.input_flag = 1;
	if (file)
		free(file);
}

void	execute_run(t_cmnd *t_cmd)
{
	char	**path;

	g_data.executor_flag = 1;
	if (is_executor(t_cmd->expand_cmnd) == 1)
		path = ft_split(g_data.path, ':');
	else
	{
		path = malloc(sizeof(char *) * 2);
		path[0] = ft_strdup("/");
		path[1] = 0;
	}
	execve_run(t_cmd, path);
	free(path[0]);
	free(path);
}

void	exec_cmnd(t_cmnd *t_cmd)
{	
	while (t_cmd)
	{
		if (t_cmd->next && t_cmd->next->is_input == 1 && !input(t_cmd->next))
			break ;
		if (is_executor(t_cmd->expand_cmnd))
			execute_run(t_cmd);
		else if (t_cmd->is_input == 2)
			execve_run(t_cmd, g_data.paths);
		else if (t_cmd->is_input == 0)
			output(t_cmd);
		t_cmd = t_cmd->next;
	}
	wait_pid_all(g_data.t_cmnd);
	close_all(g_data.t_cmnd);
}
