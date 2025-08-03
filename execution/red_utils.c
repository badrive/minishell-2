
#include "../minishel.h"

int is_redirection(t_redir *current_redir, int has_input_redir, int has_output_redir)
{
    if ((has_input_redir && current_redir->type == REDIRE_IN)
        || (has_output_redir && current_redir->type != REDIRE_IN))
    {
        ft_putstr_fd("minishell: ambiguous redirection\n", STDERR_FILENO);
        return (1);
    }
    return (0);
}

int apply_redirection(t_redir *current_redir, int *has_input_redir, int *has_output_redir)
{
    int fd;
    
    fd = open_redir_file(current_redir);
    if (fd == -1)
        return (1);

    if (current_redir->type == REDIRE_IN)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("minishell: input redirect failed");
            close(fd);
            return (1);
        }
        *has_input_redir = 1;
    }
    else
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("minishell: output redirect failed");
            close(fd);
            return (1);
        }
        *has_output_redir = 1;
    }
    close(fd);
    return (0);
}
void ft_free_2d(char **arr)
{
    int i;

    if (!arr)
        return;
    
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void int_handler(int status) 
{
    (void)status;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int skip_spaces(const char *input, int i) 
{
    while (input[i] && isspace((unsigned char)input[i]))
        i++;
    return i;
}
