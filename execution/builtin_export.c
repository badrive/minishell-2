
#include "../minishel.h"

int	is_valid_identifier(const char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	update_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*env;
	t_env	*new;
	t_env	*tmp;

	env = *env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_sorted_env(t_env *env)
{
	t_env	**array;
	t_env	*tmp;
	int		size;
	int		i, j;

	tmp = env;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return ;
	tmp = env;
	i = 0;
	while (tmp)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (array[i]->value)
			printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		else
			printf("declare -x %s\n", array[i]->key);
		i++;
	}
	free(array);
}

int	builtin_export(char **args, t_env **env_list)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal;

	if (!args[1])
	{
		print_sorted_env(*env_list);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			key = ft_substr(args[i], 0, equal - args[i]);
			if (!is_valid_identifier(key))
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				free(key);
				i++;
				continue ;
			}
			value = ft_strdup(equal + 1);
			update_env_var(env_list, key, value);
			free(key);
			free(value);
		}
		else
		{
			if (!is_valid_identifier(args[i]))
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				i++;
				continue ;
			}
			update_env_var(env_list, args[i], "");
		}
		i++;
	}
	return (0);
}
