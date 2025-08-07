/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:58:08 by w                 #+#    #+#             */
/*   Updated: 2025/08/07 22:52:44 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_lexer	*ft_cmp(char **av)
{
	t_lexer	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (av[i])
	{
		if (!strcmp(av[i], "<<"))
			handle_heredoc_p(av, &i, &tokens);
		else if (!strcmp(av[i], "<"))
			handle_input(av, &i, &tokens);
		else if (!strcmp(av[i], ">"))
			handle_output(av, &i, &tokens);
		else if (!strcmp(av[i], ">>"))
			handle_append(av, &i, &tokens);
		else
		{
			ft_lstadd_back_lexer(&tokens,
				new_node_lexer(qoute_remov(av[i], 0, 0, 0), WORD));
			i++;
		}
	}
	return (tokens);
}

int	count_lex(t_lexer *lex, t_type type)
{
	int	size;

	size = 0;
	while (lex)
	{
		if (lex->type == type)
			size++;
		lex = lex->next;
	}
	return (size);
}

t_lexer	*new_node_lexer(char *args, t_type type)
{
	t_lexer	*node;

	node = ft_malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(args);
	node->next = NULL;
	return (node);
}

t_lexer	*ft_lstlast_lexer(t_lexer *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
