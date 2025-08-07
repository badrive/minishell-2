/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:10:53 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/07 22:44:38 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	process_redirs_and_heredocs(t_lexer *lex, t_redir **redir,
		t_heredoc **heredoc)
{
	t_redir		*new1;
	t_heredoc	*new;

	while (lex)
	{
		if ((lex->type == REDIRE_IN || lex->type == REDIRE_OUT
				|| lex->type == REDIR_APPEND) && lex->next
			&& lex->next->type == FILEE)
		{
			new1 = new_node_redir(ft_strdup(lex->next->value), lex->type);
			if (new1)
				ft_lstadd_back_redir(redir, new1);
			lex = lex->next;
		}
		else if (lex->type == HEREDOC && lex->next
			&& lex->next->type == DELIMITER)
		{
			new = new_node_heredoc(ft_strdup(lex->next->value));
			if (new)
				ft_lstadd_back_heredoc(heredoc, new);
			lex = lex->next;
		}
		lex = lex->next;
	}
}

int	init_and_split(char *line, char **new_line, char ***args)
{
	*new_line = fix_line(line);
	*args = ft_split_space(*new_line);
	if (check_redirections(*args) == 0)
		return (ft_putendl_fd("minishell~$ syntax error near unexpected", 2),
			1);
	if (!*args)
		return (1);
	return (0);
}

int	create_node_from_lexer(t_lexer *lex, t_data **data)
{
	t_redir		*redir;
	t_heredoc	*heredoc;
	char		**cmds;
	t_data		*node;

	cmds = extract_cmd_args(lex);
	if (!cmds)
		return (0);
	redir = NULL;
	heredoc = NULL;
	process_redirs_and_heredocs(lex, &redir, &heredoc);
	node = new_node_cmd(cmds);
	if (!node)
		return ( 0);
	node->redir = redir;
	node->herdoc = heredoc;
	ft_lstadd_back_data(data, node);
	return (0);
}

int	handle_command(char *line, t_data **data)
{
	char	*new_line;
	char	**args;
	t_lexer	*lex;

	if (init_and_split(line, &new_line, &args))
		return (1);
	lex = ft_cmp(args);
	if (!lex)
		return (0);
	return (create_node_from_lexer(lex, data));
}

int	parse_commands(char *str, t_data **data)
{
	int		i;
	char	**pipe_split;

	if (!d_quote(str, 0, 0, 0) || !check_pipe(str))
	{
		// g_es = 2;
		ft_putendl_fd("minishell~$ syntax error near unexpected", 2);
		return (1);
	}
	pipe_split = expand_and_split(str, NULL);
	if (!pipe_split)
		return (1);
	i = 0;
	while (pipe_split[i])
	{
		if (handle_command(pipe_split[i], data))
			return (1);
		i++;
	}
	return (0);
}
