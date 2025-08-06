/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:58:08 by w                 #+#    #+#             */
/*   Updated: 2025/08/05 17:41:27 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_lexer *ft_cmp(char **av)
{
    t_lexer *tokens = NULL;
    int i = 0;

    while (av[i])
    {
        if (strcmp(av[i], "<<") == 0)
        {
            ft_lstadd_back_lexer(&tokens, new_node_lexer(av[i], HEREDOC));
            if (av[i + 1])
                ft_lstadd_back_lexer(&tokens, new_node_lexer(av[i + 1], DELIMITER));
            i += 2;
            continue;
        }
        else if (strcmp(av[i], "<") == 0)
        {
            ft_lstadd_back_lexer(&tokens, new_node_lexer(av[i], REDIRE_IN));
            if (av[i + 1])
                ft_lstadd_back_lexer(&tokens, new_node_lexer(qoute_remov(av[i + 1], 0, 0, 0), FILEE));
            i += 2;
            continue;
        }
        else if (strcmp(av[i], ">") == 0)
        {
            ft_lstadd_back_lexer(&tokens, new_node_lexer(av[i], REDIRE_OUT));
            if (av[i + 1])
                ft_lstadd_back_lexer(&tokens, new_node_lexer(qoute_remov(av[i + 1], 0, 0, 0), FILEE));
            i += 2;
            continue;
        }
        else if (strcmp(av[i], ">>") == 0)
        {
            ft_lstadd_back_lexer(&tokens, new_node_lexer(av[i], REDIR_APPEND));
            if (av[i + 1])
                ft_lstadd_back_lexer(&tokens, new_node_lexer(qoute_remov(av[i + 1], 0, 0, 0), FILEE));
            i += 2;
            continue;
        }
        else
        {
            ft_lstadd_back_lexer(&tokens, new_node_lexer(qoute_remov(av[i], 0, 0, 0), WORD));
            i++;
        }
    }
    return tokens;
}


int count_lex(t_lexer *lex, t_type type)
{
    int size = 0;
    while(lex)
    {
        if(lex->type == type)
            size++;
    lex = lex->next;
    }
    return size;
}

t_lexer *new_node_lexer(char *args,t_type type)
{
	t_lexer *node;
	
	node = ft_malloc(sizeof(t_lexer));
	if(!node)
		return NULL;
	node->type = type;
    node->value = ft_strdup(args);
	node->next = NULL;
	return node;
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

void ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new)
{
    if (!lst || !new)
        return ;
    
    if (*lst == NULL)
    {
        *lst = new; 
    }
    else
    {
        t_lexer *temp = *lst; 
        while (temp->next)    
            temp = temp->next;
        temp->next = new;     
    }
}
