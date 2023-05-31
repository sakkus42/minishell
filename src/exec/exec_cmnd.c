#include "exec.h"


int	get_size_t_cmd(t_cmnd *t_cmd)
{
	if (!t_cmd)
		return (0);
	return (1 + get_size_t_cmd(t_cmd->next));
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

void	dup2_scale(t_cmnd *t_cmd)
{
	if (t_cmd->next && t_cmd->prev)
	{
		dup2(t_cmd->prev->fd[0], 0);
		dup2(t_cmd->fd[1], 1);
	}
	else if(t_cmd->next)
		dup2(t_cmd->fd[1], 1);
	else if (t_cmd->prev)
		dup2(t_cmd->prev->fd[0], 0);
}

void	close_unnecessary_fd(t_cmnd *t_cmd)
{
	if (t_cmd->next && t_cmd->prev)
	{
		close(t_cmd->prev->fd[0]);
		close(t_cmd->fd[1]);
	}
	else if(t_cmd->next)
		close(t_cmd->fd[1]);
	else if (t_cmd->prev)
		close(t_cmd->prev->fd[0]);
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
		g_data.exit_status = 127;
		return ;
	}
	file = add_path(index, t_cmd->expand_cmnd[0]);
	id = fork();
	if (id == 0)
	{
		dup2_scale(t_cmd);
		close(t_cmd->fd[0]);
		close(t_cmd->fd[1]);
		execve(file, t_cmd->expand_cmnd, g_data.env);
		exit(0);
	}
	close_unnecessary_fd(t_cmd);
	waitpid(id, &(g_data.exit_status), 0);
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	free(file);
}

void	output(t_cmnd *t_cmd)
{
	int		id;
	int 	fd;
	char	c;

	if (!ft_strncmp(t_cmd->expand_cmnd[0], ">", ft_strlen(t_cmd->expand_cmnd[0])) &&
		!access(t_cmd->expand_cmnd[1], F_OK))
			unlink(t_cmd->expand_cmnd[1]);
	fd = open(t_cmd->expand_cmnd[1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
	{
		printf("Minishell: %s: Permission denied\n", t_cmd->expand_cmnd[1]);
		return ;
	}
	id = fork();
	if (id == 0)
	{
		dup2(fd, 1);
		close(fd);
		while (read(t_cmd->prev->fd[0], &c, 1))
			printf("%c", c);
		exit(0);
	}
	close(fd);
	waitpid(id, NULL, 0);
}

void	heredoc(t_cmnd *t_cmd)
{
	(void)t_cmd;
	return ;
}

void	exec_cmnd(t_cmnd *t_cmd)
{
	if (!g_data.pipe_count && get_size_t_cmd(g_data.t_cmnd) == 1)
	{
		execve_run(g_data.t_cmnd);
		return ;
	}
	while (t_cmd)
	{
		if (t_cmd->is_input == 2)
			execve_run(t_cmd);
		else if (t_cmd->is_input == 0)
			output(t_cmd);
		else if (t_cmd->is_input == 1 && !ft_strncmp(t_cmd->expand_cmnd[0], "<", ft_strlen(t_cmd->expand_cmnd[0])))
		{
			t_cmd = t_cmd->next;
			continue;
		}
		else
			heredoc(t_cmd);

		t_cmd = t_cmd->next;
	}
	close_all(g_data.t_cmnd); 
}