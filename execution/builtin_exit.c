#include "../minishel.h"

int builtin_exit(char **args)
{
    int status = 0;
    
    if (args[1]) 
    {
        status = ft_atoi(args[1]);
        if (status == 0 && args[1][0] != '0') 
        {
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
            status = 2;
        }
    }
    
    printf("exit\n");
    exit(status);
    
}