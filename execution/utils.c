#include "../minishel.h"

int	count_env_vars(t_env *env)
{
	int	count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	free_partial_envp(char **envp, int i)
{
	int	j = 0;

	while (j < i)
		free(envp[j++]);
	free(envp);
}

char *get_enviroment(t_env *env, char *key)
{
    if (!env || !key)
        return NULL;
    
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}
char	*is_direct_path_or_null(char *cmd, t_env *env)
{
	char	*path_val;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') || access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_val = get_enviroment(env, "PATH");
	if (!path_val)
		return (NULL);
	return (ft_strdup(path_val));
}

char	*search_in_paths(char **paths, char *cmd)
{
	int		i = 0;
	char	*tmp;
	char	*full;

	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			break ;
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			break ;
		if (access(full, X_OK) == 0)
		{
			ft_free_2d(paths);
			return (full);
		}
		free(full);
		i++;
	}
	ft_free_2d(paths);
	return (NULL);
}