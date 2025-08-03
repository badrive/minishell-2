/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:13:54 by w                 #+#    #+#             */
/*   Updated: 2025/08/02 11:53:38 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_data *new_node(char **args)
{
	t_data *node;
	
	node = ft_malloc(sizeof(t_data));
	if(!node)
		return NULL;
	node->cmds = args;
	//node->cmd_lst = malloc(sizeof(t_cmd_lst));
	node->redir = NULL;
	node->herdoc = NULL;
	node->next = NULL;
	return node;
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

void ft_lstadd_back2(t_data **lst, t_data *new)
{
    if (!lst || !new)
        return ;
    
    if (*lst == NULL)
    {
        *lst = new;  // First node
    }
    else
    {
        t_data *temp = *lst;  // ✅ Use temporary pointer
        while (temp->next)    // ✅ Traverse without modifying original
        {
            temp = temp->next;
        }
        temp->next = new;     // ✅ Add new node at the end
    }
}