/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:18:26 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/02 23:07:43 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishel.h"

// void    execution(t_data *data);



int is_redir_char(char c) 
{
    return (c == '>' || c == '<');
}

int check_pipe_syntax(const char *input, int i)
{
	int before;
	int after;

	if (i == 0 || input[i + 1] == '\0')
	{
		ft_putstr_fd("Syntax error: Misplaced pipe '|'\n", STDERR_FILENO);
		return (1);
	}
	before = i - 1;
	while (before >= 0 && input[before] && isspace((unsigned char)input[before]))
		before--;
	after = skip_spaces(input, i + 1);
	if (before < 0 || input[after] == '|' || input[after] == '\0')
	{
		ft_putstr_fd("Syntax error: Invalid pipe usage\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int check_redirection_syntax(const char *input, int *i)
{
	//int start;
	int count;
	char type;

	//start = *i;
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

int check_syntax_errors(const char *input)
{
	int i;

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
			continue;
		}
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    (void)envp;

    char *str = NULL;
    t_data *data = NULL;
    t_env   *env;

    env = init_env_list(envp);
    signal(SIGINT, int_handler);

    while (1)
    {
        str = readline("minishell~$ ");
        if (!str)
		{
			//free all
            break;
		}

        if (parse_commands(str,&data))
		{
			//free all
			continue ;
		}
        execute_command(data, env);
		// // free
		free_list(data);
		data = NULL;
        add_history(str);
        free(str);
    }
	ft_free_all();
    return 0;
}
