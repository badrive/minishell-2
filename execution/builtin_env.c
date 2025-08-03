#include "../minishel.h"

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	int		i;
	char	*equal_sign;
	size_t	key_len;
	t_env	*node;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (!equal_sign)
			continue ;
		key_len = equal_sign - envp[i];
		node = malloc(sizeof(t_env));
		if (!node)
			return (NULL);
		node->key = malloc(key_len + 1);
		if (!node->key)
		{
			free(node);
			return (NULL);
		}
		ft_strlcpy(node->key, envp[i], key_len + 1);
		node->value = ft_strdup(equal_sign + 1);
		node->next = NULL;
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (head);
}

int builtin_env(t_data *min)
{
	t_env *env;
	env = min->env;
	while (env)
	{
		if (env->value && env->key)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	char	input[100];

	env_list = init_env_list(envp);
	(void)argc, (void)argv;
	while (1)
	{
		printf("minishell> ");
		if (!fgets(input, sizeof(input), stdin))
			break ;
		// Remove newline
		input[strcspn(input, "\n")] = 0;
		if (strcmp(input, "env") == 0)
		{
			builtin_env(env_list);
		}
			
		else if (strcmp(input, "exit") == 0)
			break ;
		else
			printf("Command not found: %s\n", input);
	}
	free_env_list(env_list);
	return (0);
}
*/