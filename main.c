/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:18:26 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/07 20:21:02 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}

int	check_pipe_syntax(const char *input, int i)
{
	int	before;
	int	after;

	if (i == 0 || input[i + 1] == '\0')
	{
		ft_putstr_fd("Syntax error: Misplaced pipe '|'\n", STDERR_FILENO);
		return (1);
	}
	before = i - 1;
	while (before >= 0 && input[before]
		&& isspace((unsigned char)input[before]))
		before--;
	after = skip_spaces(input, i + 1);
	if (before < 0 || input[after] == '|' || input[after] == '\0')
	{
		ft_putstr_fd("Syntax error: Invalid pipe usage\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_redirection_syntax(const char *input, int *i)
{
	int		count;
	char	type;

	count = 1;
	type = input[*i];
	(*i)++;
	if (input[*i] == type)
	{
		count++;
		(*i)++;
	}
	if (input[*i] == type)
	{
		ft_putstr_fd("Syntax error: Too many characters\n", STDERR_FILENO);
		return (1);
	}
	*i = skip_spaces(input, *i);
	if (input[*i] == '\0' || input[*i] == '|' || is_redir_char(input[*i]))
	{
		ft_putstr_fd("Syntax error: Redirection without target\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_syntax_errors(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (check_pipe_syntax(input, i))
				return (1);
		}
		else if (input[i] == '>' || input[i] == '<')
		{
			if (check_redirection_syntax(input, &i))
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_data	*data;
	t_env	*env;

	(void)ac;
	(void)av;
	(void)envp;
	str = NULL;
	data = NULL;
	env = init_env_list(envp);
	signal(SIGINT, int_handler);
	while (1)
	{
		str = readline("minishell~$ ");
		if (!str)
			break ;
		if (parse_commands(str, &data))
			continue ;
		execute_command(data, env);
		data = NULL;
		add_history(str);
		free(str);
	}
	ft_free_all();
	return (0);
}
