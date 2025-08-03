
# include "../minishel.h"

int echo_command(t_data *data)
{
    char **args;
    int i = 1;
    int nwl = 1;

    args = data->cmds;
    if (!args)
        return 1;

    while (args[i] && args[i][0] == '-' && args[i][1] == 'n') {
        int j = 2;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] != '\0')
            break;
        nwl = 0;
        i++;
    }
    
    while (args[i]) 
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (nwl)
        printf("\n");
    return (0);
}
/*
int main(int argc, char *argv[])
{
    t_data data;

    // Allocate and copy command-line arguments (argv)
    data.cmds = malloc(sizeof(char *) * (argc + 1));
    for (int i = 0; i < argc; i++) {
        data.cmds[i] = strdup(argv[i]);
    }
    data.cmds[argc] = NULL; // NULL-terminate the array

    // Call the echo command
    echo_command(&data);

    // Free memory
    for (int i = 0; i < argc; i++) {
        free(data.cmds[i]);
    }
    free(data.cmds);

    return 0;
}
*/
