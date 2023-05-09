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

typedef struct s_token
{
	char *cmnd;
	char *cmnd_file;
	int	if_red;
	int	if_quot;
	int	if_pipe;
	struct s_token *next;
}				t_token;

typedef struct s_cmnd
{
	char	*cmnd;
} t_cmnd;

typedef struct s_data
{
	int		is;
	int		LEXFLAG;
	char	*input;
	char 	**paths;
	char 	**env;
	char	**inp_parser;

	t_token	*t_token;
} t_data;

t_data 	g_data;	
int		find_dir(char **path, char *cmd);
void	exit_free();
void	signal_cntrl();
void	ctrl_c(int sig);
void	ctrl_d();
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*lexer();

#endif