#ifndef MINISHEL_H
# define MINISHEL_H

#include "libft/libft.h"
#include "parsing/parsing.h"
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

// Add to minishel.h
int builtin_cd(char **args, t_env *env);
int builtin_export(char **args, t_env **env_list);
int builtin_exit(char **args);
char *get_enviroment(t_env *env, char *key);
void	update_env_var(t_env **env_list, char *key, char *value);

#endif