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
	if (t_cmd->next && t_cmd->prev && t_cmd->next->input_fd == -1)
	{
		dup2(t_cmd->prev->fd[0], 0);
		dup2(t_cmd->fd[1], 1);
	}
	else if(t_cmd->next && t_cmd->next->input_fd == -1)
		dup2(t_cmd->fd[1], 1);
	else if (t_cmd->prev)
		dup2(t_cmd->prev->fd[0], 0);
	if (t_cmd->next && t_cmd->next->input_fd != -1)
		dup2(t_cmd->next->input_fd, 0);
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

void	file_add(char **file, char **paths, char *expand_cmnd)
{
	int	index;

	index = find_dir(paths, expand_cmnd);
	if (index == -1 && !built_in_ctl(expand_cmnd))
	{
		printf("minishell: %s: command not found\n", expand_cmnd);
		g_data.exit_status = 127;
		*file = NULL;
		return ;
	}
	*file = add_path(index, expand_cmnd, paths);
}

void	execve_run(t_cmnd *t_cmd, char **paths)
{
	int		id;
	char	*file;

	if (ft_strnstr(t_cmd->expand_cmnd[0], "./", 2))
		file_add(&file, paths, t_cmd->expand_cmnd[0] + 2);
	else
		file_add(&file, paths, t_cmd->expand_cmnd[0]);
	id = fork();
	if (id == 0)
	{
		dup2_scale(t_cmd);
		g_data.id = 1;
		close(t_cmd->fd[0]);
		close(t_cmd->fd[1]);
		if (built_in_ctl(t_cmd->expand_cmnd[0]))
			ft_builtins(t_cmd->expand_cmnd);
		else
			execve(file, t_cmd->expand_cmnd, g_data.env);
		exit(0);
	}
	close_unnecessary_fd(t_cmd);
	waitpid(id, &(g_data.exit_status), 0);
	g_data.id = 0;
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	if (file)
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
	int		is;
	
	is = 1;
	while (ft_strcmp(t_cmd->expand_cmnd[1], g_data.input[0]))
	{
		g_data.heredoc_flag = 1;
		if (g_data.input[0])
			free(g_data.input[0]);
		g_data.input[0] = readline("heredoc>");
		if (!g_data.heredoc_flag)
		{
			g_data.heredoc_flag = 1;
			return ;
		}
		if (ft_strcmp(t_cmd->expand_cmnd[1], g_data.input[0]))
		{
			ft_putstr_fd(g_data.input[0], t_cmd->fd[1]);
			ft_putstr_fd("\n", t_cmd->fd[1]);
		}
	}
	g_data.heredoc_flag = 0;
	close(t_cmd->fd[1]);
	t_cmd->input_fd = t_cmd->fd[0];
}

int	is_directory(char *expand_cmnd)
{
	DIR	*d;

	d = opendir(expand_cmnd);
	if (d)
		closedir(d);
	return (d != NULL);
}

int	input(t_cmnd *t_cmd)
{
	int	fd;
	int	open_flag;

	if (!ft_strcmp(t_cmd->expand_cmnd[0], "<") && !access(t_cmd->expand_cmnd[1], F_OK))
	{
		if (is_directory(t_cmd->expand_cmnd[1]))
			open_flag = O_DIRECTORY;
		else
			open_flag = O_RDWR;
		fd = open(t_cmd->expand_cmnd[1], open_flag);
		if (fd == -1)
		{
			printf("minishell: %s:permission denied\n", t_cmd->expand_cmnd[1]);
			return (0);
		}
		t_cmd->input_fd = fd;
	}
	else if (!ft_strcmp(t_cmd->expand_cmnd[0], "<<"))
	{
		heredoc(t_cmd);
		if (g_data.heredoc_flag)
			return (0);
	}
	else
	{
		printf("minishell: %s: No such file or directory\n", t_cmd->expand_cmnd[1]);
		return (0);
	}
	return (1);
}

void	exec_cmnd(t_cmnd *t_cmd)
{
	char	**paths;

	if (!g_data.pipe_count && get_size_t_cmd(g_data.t_cmnd) == 1)
	{
		if (built_in_ctl(t_cmd->expand_cmnd[0]))
			ft_builtins(t_cmd->expand_cmnd);
		else if (ft_strnstr(t_cmd->expand_cmnd[0], "./", 2))
		{
			paths = ft_split(getenv("PWD"), ':');
			execve_run(g_data.t_cmnd, paths);
			free(paths[0]);
			free(paths);
		}
		else
			execve_run(g_data.t_cmnd, g_data.paths);
		return ;
	}
	while (t_cmd)
	{
		if (t_cmd->next && t_cmd->next->is_input == 1)
		{
			if(!input(t_cmd->next))
				break;
		}
		if (t_cmd->is_input == 2)
			execve_run(t_cmd, g_data.paths);
		else if (t_cmd->is_input == 0)
			output(t_cmd);
		t_cmd = t_cmd->next;
	}
	close_all(g_data.t_cmnd); 
}