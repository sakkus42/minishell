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

struct s_data
{
	char	*input;
	char 	**paths;
	char 	**env;
	char	**inp_parser;
	int		is;

} t_data;


void	builtcmds();
int 	find_dir(char *path, char *cmd);
void	exit_free();
void	input_parser();
#endif