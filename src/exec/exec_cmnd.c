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
	file = NULL;
	t_cmd->id = fork();
	if (t_cmd->id == 0)
	{
		file_add(&file, paths, t_cmd);
		dup2_scale(t_cmd);
		close_all(g_data.t_cmnd);
		if (built_in_ctl(t_cmd->expand_cmnd_lower[0]))
			ft_builtins(t_cmd->expand_cmnd_lower, t_cmd->expand_cmnd);
		else if (execve(file, t_cmd->expand_cmnd, g_data.env) == -1 && \
				!is_executor(t_cmd->expand_cmnd))
		{
			t_cmd->error_flag = 1;
			exit(127);
		}
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

void	get_paths()
{
	int		index;
	char	**path;

	if (g_data.paths)
	{
		index = 0;
		while (g_data.paths[index])
			free(g_data.paths[index++]);
		free(g_data.paths);
	}
	index = is_env("PATH");
	if (index == -1)
	{
		g_data.paths = NULL;
		return ;
	}
	path = ft_split(g_data.env[index], '=');
	g_data.paths = ft_split(path[1], ':');
	free(path[0]);
	free(path[1]);
	free(path);
}

int	input_output(t_cmnd *t_cmd)
{
	while (t_cmd)
	{
		if (t_cmd->is_input == 1)
		{
			if (input(t_cmd))
				return (0);
		}
		else if (t_cmd->is_input == 0 && t_cmd)
		{
			output(t_cmd);
		}
		t_cmd = t_cmd->next;
	}
	return (1);
}

void	exec_cmnd(t_cmnd *t_cmd)
{
	int		is;

	printf("g_data.pipe_count: %d\n", g_data.pipe_count);
	is = input_output(g_data.t_cmnd);
	while (t_cmd && is && !g_data.heredoc_flag)
	{
		get_paths();
		if (!g_data.paths && !built_in_ctl(t_cmd->expand_cmnd_lower[0]))
		{
			printf("minishell: %s: No such file or directory\n", t_cmd->expand_cmnd[0]);
			g_data.exit_status = 127;
		}
		else if (is_executor(t_cmd->expand_cmnd))
			execute_run(t_cmd);
		else if (t_cmd->is_input == 2)
			execve_run(t_cmd, g_data.paths);
		t_cmd = t_cmd->next;
	}
	wait_pid_all(g_data.t_cmnd);
	close_all(g_data.t_cmnd);
	if (!is)
		g_data.exit_status = 1;
}
