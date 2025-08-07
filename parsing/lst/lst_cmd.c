/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:13:54 by w                 #+#    #+#             */
/*   Updated: 2025/08/07 20:03:58 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_data	*new_node(char **args)
{
	t_data	*node;

	node = ft_malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->cmds = args;
	node->redir = NULL;
	node->herdoc = NULL;
	node->next = NULL;
	return (node);
}

t_data	*ft_lstlast2(t_data *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back2(t_data **lst, t_data *new)
{
	t_data	*temp;

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
