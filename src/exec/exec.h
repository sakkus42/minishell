#ifndef EXEC_H
# define EXEC_H
# include "../../include/minishell.h"

typedef struct s_pipe{
	int	fd[2];
	struct s_pipe *next;
	struct s_pipe *prev;
}	t_pip;

int		is_executor(char **expand_cmd);
int		get_size_t_cmd(t_cmnd *t_cmd);
int		is_directory(char *expand_cmnd);
int		input(t_cmnd *t_cmd);
void	file_add(char **file, char **paths, t_cmnd *t_cmd);
void	heredoc(t_cmnd *t_cmd);
void	output(t_cmnd *t_cmd);
void	dup2_scale(t_cmnd *t_cmd);
void	close_all(t_cmnd *t_cmd);
void	close_unnecessary_fd(t_cmnd *t_cmd);
void	wait_pid_all(t_cmnd *t_cmd);

#endif