#ifndef BUILTIN_H
#define BUILTIN_H

#include "../../include/minishell.h"

int		built_in_ctl(char *str);
char	*new_str(char *str, char *new);
char	*get_env(char *key);
void	free_double_pointer(char ***str);
void	ft_echo(char **arg);
void	n_ctl(char **arg, int i);
void	ft_cd(char *dest, char *old_dir);
void	set_tmp(char **tmp, int *i);
void	set_pwds(char *old_dir, int find);
void	update_env_pwds(char *old_dir);
void	update_env(char *keyval, int state);
void	add_env_success(char *keyval, char ***tmp, int *i);
void	set_keys(char *keyval, int *find, int *i);
void	do_export(char **str);
void	print_export(void);
void	set_key_and_value(char **key, char **value, int *i);
void	print_env(char **str);
void	ft_unset(char **env, char *str);

#endif