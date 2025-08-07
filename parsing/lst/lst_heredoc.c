/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:00:33 by w                 #+#    #+#             */
/*   Updated: 2025/08/07 20:08:15 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_heredoc	*new_node_heredoc(char *dlm)
{
	t_heredoc	*node;

	node = ft_malloc(sizeof(t_heredoc));
	if (!node)
		return (NULL);
	node->delimeter = dlm;
	node->next = NULL;
	return (node);
}

t_heredoc	*ft_lstlast_heredoc(t_heredoc *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_heredoc(t_heredoc **lst, t_heredoc *new)
{
	t_heredoc	*temp;

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
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}
