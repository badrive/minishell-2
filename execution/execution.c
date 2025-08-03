/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:43:46 by ahmben-a          #+#    #+#             */
/*   Updated: 2025/07/17 23:38:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>


void handle_redirections(t_redir *redir);
int open_redir_file(t_redir *redir);


char	**build_envp_array(t_env *env)
{
	int		count;
	char	**envp;
	int		i;
	t_env	*tmp;

	count = count_env_vars(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (i < count)
	{
		envp[i] = join_key_value(tmp);
		if (!envp[i])
		{
			free_partial_envp(envp, i);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	*direct;
	char	**paths;
	//char	*path_val;

	direct = is_direct_path_or_null(cmd, env);
	if (!direct)
		return (NULL);
	if (ft_strcmp(direct, cmd) == 0)
		return (direct);
	paths = ft_split(direct, ':');
	free(direct);
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}

int	handle_heredoc(t_heredoc *heredoc)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

    while(heredoc)
    {
	if (setup_heredoc_pipe(heredoc, pipefd, &pid) == -1)
		return (-1);
	if (pid == 0)
		run_heredoc_child(heredoc, pipefd[1]);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(pipefd[0]);
		return (-1);
	}
    heredoc = heredoc->next;
    }
	return (pipefd[0]);
}

int execute_builtin(t_data *node, t_env **env)
{
    char *cmd; 
    cmd = node->cmds[0];

    if (ft_strcmp(cmd, "cd") == 0)
        return builtin_cd(node->cmds, *env);
    else if (ft_strcmp(cmd, "echo") == 0)
        return echo_command(node);
    else if (ft_strcmp(cmd, "pwd") == 0)
        return get_pwd(node);
    else if (ft_strcmp(cmd, "export") == 0)
        return builtin_export(node->cmds, env);
    else if (ft_strcmp(cmd, "unset") == 0)
        return builtin_unset(node->cmds, env);
    else if (ft_strcmp(cmd, "env") == 0)
        return builtin_env(node);
    else if (ft_strcmp(cmd, "exit") == 0)
        return builtin_exit(node->cmds);
    return 0;
}

int execute_command(t_data *data, t_env *env)
{
    int pipefd[2];
    int prev_fd = -1;
    pid_t last_pid = 0;
    int last_status = 0;
    char **envp = build_envp_array(env);
    t_data *node = data;

    for (t_data *tmp = data; tmp; tmp = tmp->next)
        tmp->env = env;

    while (node)
    {
        int has_next = (node->next != NULL);
        int is_builtin_cmd = node->cmds && is_builtin(node->cmds[0]);
        int should_run_in_parent = is_builtin_cmd && is_parent_builtin(node->cmds[0]) && !has_next && prev_fd == -1;

        if (should_run_in_parent)
        {
            handle_redirections(node->redir);
            return execute_builtin(node, &env);
        }

        if (has_next && pipe(pipefd) == -1)
        {
            perror("minishell: pipe");
            free(envp);
            return 1;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("minishell: fork");
            free(envp);
            return 1;
        }

        if (pid == 0)
        {
            if (node->herdoc)
            {
                int heredoc_fd = handle_heredoc(node->herdoc);
                if (heredoc_fd == -1)
                    exit(1);
                if (dup2(heredoc_fd, STDIN_FILENO) == -1)
                {
                    perror("minishell: heredoc dup2");
                    close(heredoc_fd);
                    exit(1);
                }
                close(heredoc_fd);
            }

            handle_redirections(node->redir);

            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            if (has_next)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            if (!node->cmds || !node->cmds[0])
            {
                //fprintf(stderr, minishell: empty command\n"");
                exit(127);
            }

            if (is_builtin_cmd)
            {
                int result = execute_builtin(node, &env);
                exit(result);
            }

            char *path = get_cmd_path(node->cmds[0], node->env);
            if (!path)
            {
                fprintf(stderr, "minishell: %s: command not found\n", node->cmds[0]);
                exit(127);
            }

            execve(path, node->cmds, envp);
            perror("minishell: execve");
            exit(126);
        }

        if (prev_fd != -1)
            close(prev_fd);
        if (has_next)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        else
        {
            last_pid = pid;
        }
        node = node->next;
    }

    int status;
    pid_t wpid;
    while ((wpid = wait(&status)) != -1)
    {
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                last_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                last_status = 128 + WTERMSIG(status);
        }
    }
    free(envp);
    return last_status;
}

void handle_redirections(t_redir *redir)
{
    int stdin_redirected = 0;
    int stdout_redirected = 0;

    while (redir)
    {
        if (is_redirection(redir, stdin_redirected, stdout_redirected))
            exit(1);
        if (apply_redirection(redir, &stdin_redirected, &stdout_redirected))
            exit(1);
        redir = redir->next;
    }
}

int open_redir_file(t_redir *redir)
{
    if (!redir || !redir->filename) {
        ft_putstr_fd("minishell: invalid redirection\n",STDERR_FILENO);
        return -1;
    }

    int flags = 0;
    if (redir->type == REDIRE_IN)
        flags = O_RDONLY;
    else if (redir->type == REDIRE_OUT)
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    else if (redir->type == REDIR_APPEND)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else {
        ft_putstr_fd("minishell: unknown redirection type\n",STDERR_FILENO);
        return -1;
    }

    int fd = open(redir->filename, flags, 0644);
    if (fd == -1)
        perror("minishell: open");
    return fd;
}
