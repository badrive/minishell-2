# include "../minishel.h"

int    get_pwd(t_data *data)
{
    char cwd[1024];
    if (data && data->cmds[1])
    {
        ft_putendl_fd("to many arguments",2);
        return 1;
    }
    if (getcwd(cwd,sizeof(cwd)) != NULL)
        printf ("%s\n",cwd);
    else
        perror("pwd");
    return (0);
}
/*

int main(int argc, char **argv)
{
    t_data data;

    // Simulate parsed commands (skip program name)
    data.cmds = argv + 1;

    // Check if it's the "pwd" command
    if (data.cmds[0] && strcmp(data.cmds[0], "pwd") == 0)
        get_pwd(&data);
    else
        fprintf(stderr, "Unknown or missing command\n");

    return 0;
}
*/
