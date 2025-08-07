/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:59:44 by w                 #+#    #+#             */
/*   Updated: 2025/08/07 20:17:54 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_redir	*new_node_redir(char *file, t_type type)
{
	t_redir	*node;

	node = ft_malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->filename = file;
	node->next = NULL;
	return (node);
}

t_redir	*ft_lstlast_redir(t_redir *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

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
