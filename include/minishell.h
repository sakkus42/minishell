#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <errno.h>	

typedef struct s_token
{
	char	**cmnd;
	int		if_red;
	int		if_quot;
	int		if_pipe;
	struct	s_token *next;
}				t_token;

typedef struct s_cmnd
{
	char	**expand_cmnd;
	char	**expand_cmnd_lower;
	char	**cmnd_path;
	int		is_input;
	int		input_fd;
	int		output_fd;
	int		id;
	int		fd[2];
	int		context;
	int		error_flag;
	struct	s_cmnd *next;
	struct	s_cmnd *prev;
} t_cmnd;

typedef struct s_data
{
	int		is;
	int		pipe_count;
	int		heredoc_flag;
	int		input_flag;
	int		executor_flag;
	int		exit_status;
	char	**input;
	char 	**paths;
	char 	**env;
	char	path[4096];
	int		echo;
	int		id;
	t_token	*t_token;
	t_cmnd	*t_cmnd;
} t_data;

int		find_dir(char **path, char *cmd);
int		built_in_ctl(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	signal_cntrl();
void	ctrl_d();
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstadd_back_t_cmnd(t_cmnd **lst, t_cmnd *new);
void	ft_print_struct(t_cmnd *t_cmd);
void	free_token(t_token *t_tok);
void	exit_free(int is);
void	parser();
void	exec_cmnd(t_cmnd *t_cmd);
char	*add_path(int index, char *cmnd, char **paths);
void	init_program(char **envp);
void	ft_builtins(char **cmnd, char **cmnd_upper);
void	upper_to_lower(t_cmnd *t_cmd);
int		size_double(char **str);
int		is_env(char *str);
void	get_paths();
t_token	*lexer();
t_data 	g_data;

void	func();
#endif