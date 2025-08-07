/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:04:35 by w                 #+#    #+#             */
/*   Updated: 2025/08/07 22:39:19 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	*new_node_cmd(char **cmds)
{
	t_data	*new;

	new = ft_malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->cmds = cmds;
	new->redir = NULL;
	new->herdoc = NULL;
	new->next = NULL;
	new->env = NULL;
	return (new);
}

void	ft_lstadd_back_data(t_data **lst, t_data *new)
{
	t_data	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_lexer	*skip_redirection(t_lexer *lex)
{
	if (lex->type == REDIRE_IN || lex->type == REDIRE_OUT
		|| lex->type == REDIR_APPEND || lex->type == HEREDOC)
	{
		lex = lex->next;
		if (lex && lex->type == WORD)
			lex = lex->next;
	}
	else
		lex = lex->next;
	return (lex);
}

char	**extract_cmd_args(t_lexer *lex)
{
	t_lexer	*tmp;
	char	**cmds;

	int (count), (i);
	count = 0;
	i = 0;
	tmp = lex;
	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		tmp = skip_redirection(tmp);
	}
	cmds = ft_malloc(sizeof(char *) * (count + 1));
	if (!cmds)
		return (NULL);
	while (lex)
	{
		if (lex->type == WORD)
			cmds[i++] = ft_strdup(lex->value);
		lex = skip_redirection(lex);
	}
	cmds[i] = NULL;
	return (cmds);
}
