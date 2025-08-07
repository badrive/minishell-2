/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:20:28 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/07 22:53:01 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	handle_heredoc_p(char **av, int *i, t_lexer **tokens)
{
	ft_lstadd_back_lexer(tokens, new_node_lexer(av[*i], HEREDOC));
	if (av[*i + 1])
		ft_lstadd_back_lexer(tokens, new_node_lexer(av[*i + 1], DELIMITER));
	*i += 2;
}

void	handle_input(char **av, int *i, t_lexer **tokens)
{
	ft_lstadd_back_lexer(tokens, new_node_lexer(av[*i], REDIRE_IN));
	if (av[*i + 1])
		ft_lstadd_back_lexer(tokens,
			new_node_lexer(qoute_remov(av[*i + 1], 0, 0, 0), FILEE));
	*i += 2;
}

void	handle_output(char **av, int *i, t_lexer **tokens)
{
	ft_lstadd_back_lexer(tokens, new_node_lexer(av[*i], REDIRE_OUT));
	if (av[*i + 1])
		ft_lstadd_back_lexer(tokens,
			new_node_lexer(qoute_remov(av[*i + 1], 0, 0, 0), FILEE));
	*i += 2;
}

void	handle_append(char **av, int *i, t_lexer **tokens)
{
	ft_lstadd_back_lexer(tokens, new_node_lexer(av[*i], REDIR_APPEND));
	if (av[*i + 1])
		ft_lstadd_back_lexer(tokens,
			new_node_lexer(qoute_remov(av[*i + 1], 0, 0, 0), FILEE));
	*i += 2;
}
