# include "../minishel.h"


int builtin_cd(char **args, t_env *env)
{
    char *path = args[1];
    char cwd[1024];
    char *oldpwd;
    char *newpwd;

    if (!path || ft_strcmp(path, "~") == 0) 
    {
        path = get_enviroment(env, "HOME");
        if (!path) {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            return 1;
        }
    }
     else if (ft_strcmp(path, "-") == 0) 
    {
        path = get_enviroment(env, "OLDPWD");
        if (!path) {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            return 1;
        }
        printf("%s\n", path);
    }

    if (getcwd(cwd, sizeof(cwd))) 
    {
        oldpwd = ft_strdup(cwd);
        if (!oldpwd) {
            perror("minishell: cd");
            return 1;
        }
    } else 
    {
        perror("minishell: cd");
        return 1;
    }

    if (chdir(path) != 0) 
    {
        fprintf(stderr, "minishell: cd: %s: %s\n", path, strerror(errno));
        free(oldpwd);
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd))) 
    {
        newpwd = ft_strdup(cwd);
        if (!newpwd) {
            perror("minishell: cd");
            free(oldpwd);
            return 1;
        }
    }
     else 
    {
        perror("minishell: cd");
        free(oldpwd);
        return 1;
    }

    update_env_var(&env, "OLDPWD", oldpwd);
    update_env_var(&env, "PWD", newpwd);
    
    free(oldpwd);
    free(newpwd);
    return 0;
}

// int builtin_cd(t_data *data)
// {
//     // char *path;

//     if (!data->cmds[1])
//     {
//         perror("error no arguments");
//         return 1;
//     }
//     else if (data->cmds[1] && data->cmds[2])
//     {
//         perror("too many arguments");
//         return 1;
//     }
//     else if (data->cmds[1] && chdir(data->cmds[1]) == -1)
//     {
//         perror("cd");
//         return 1;
//     }
//     return (0);
// }
/*
int main(int argc, char **argv)
{
    t_data data;

    // Simulate input: "./program cd /home"
    if (argc < 2) {
        fprintf(stderr, "Usage: %s cd <path>\n", argv[0]);
        return 1;
    }

    data.cmds = argv + 1; // Skip program name

    cd(&data);
    char cwd[4096];
    printf("%s\n", getcwd(cwd,sizeof(cwd)));
}
*/