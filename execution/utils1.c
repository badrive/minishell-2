
#include "../minishel.h"

char	*join_key_value(t_env *tmp)
{
	char	*joined;
	char	*result;

	joined = ft_strjoin(tmp->key, "=");
	if (!joined)
		return (NULL);
	result = ft_strjoin(joined, tmp->value);
	free(joined);
	return (result);
}
int	setup_heredoc_pipe(t_heredoc *heredoc, int *pipefd, pid_t *pid)
{
	if (!heredoc || !heredoc->delimeter)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		perror("minishell: heredoc pipe failed");
		return (-1);
	}
	*pid = fork();
	if (*pid < 0)
	{
		perror("minishell: heredoc fork failed");
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	return (0);
}

void	run_heredoc_child(t_heredoc *heredoc, int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);  // Enable Ctrl+C in child
	line = NULL;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, heredoc->delimeter) == 0)
			break;
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(write_fd);  // Close write end of the pipe
	exit(0);          // Exit child process
}


int is_builtin(char *cmd)
{
    if (!cmd) return 0;
    return (ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}

int is_child_safe_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "env") == 0);
}

int is_parent_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}
