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

typedef struct s_data
{
	char	*input;
	char 	**paths;
	char 	**env;
	char	**inp_parser;
	char	**lex_array;
	int		is;
	int		LEXFLAG;

} t_data;

t_data g_data;

int 	find_dir(char *path, char *cmd);
int		parser();
char	**lexer();
void	exit_free();
void	signal_cntrl();
void	ctrl_c(int sig);
void	ctrl_d();

#endif