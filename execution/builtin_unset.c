#include "../minishel.h"
#include <string.h>
int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

void remove_variable(t_env **env, char *to_remove)
{
    t_env *current = *env;
    t_env *prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, to_remove) == 0)
        {
            if (prev == NULL)
                *env = current->next; // removing head
            else
                prev->next = current->next; // skip current

            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
int builtin_unset(char **args, t_env **env_list)
{
    int i = 1;
    while (args[i])
    {
        remove_variable(env_list, args[i]);
        i++;
    }
    return (0);
}
/*
int main(void)
{
    // Manually create env list: PATH -> HOME -> USER
    t_env *env1 = malloc(sizeof (t_env));
    t_env *env2 = malloc(sizeof (t_env));
    t_env *env3 = malloc(sizeof (t_env));

    env1->key = strdup("PATH");
    env1->value = strdup("/usr/bin");
    env1->next = env2;

    env2->key = strdup("HOME");
    env2->value = strdup("/home/user");
    env2->next = env3;

    env3->key = strdup("USER");
    env3->value = strdup("ahmed");
    env3->next = NULL;

    t_env *env_list = env1;

    // Print before unset
    printf("Before unset:\n");
    t_env *tmp = env_list;
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }

    // Simulate unset HOME
    char *args[] = {"unset", "HOME", NULL};
    builtin_unset(args, &env_list);

    // Print after unset
    printf("\nAfter unset:\n");
    tmp = env_list;
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }

    // Free remaining nodes
    while (env_list)
    {
        t_env *next = env_list->next;
        free(env_list->key);
        free(env_list->value);
        free(env_list);
        env_list = next;
    }

    return 0;
}
*/