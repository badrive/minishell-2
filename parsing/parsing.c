/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:04:35 by w                 #+#    #+#             */
/*   Updated: 2025/08/03 20:53:43 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static void free_lexer(t_lexer *lex)
{
    // Don't free any tracked memory - ft_free_all() will handle it
    t_lexer *tmp;
    while (lex)
    {
        tmp = lex;
        lex = lex->next;
        // Remove all free() calls:
        // free(tmp->value);  // Don't free - tracked by ft_malloc
        // free(tmp);         // Don't free - tracked by ft_malloc
    }
}

static t_data *new_node_cmd(char **cmds)
{
    t_data *new = ft_malloc(sizeof(t_data));
    if (!new)
        return NULL;
    new->cmds = cmds;
    new->redir = NULL;
    new->herdoc = NULL;
    new->next = NULL;
    new->env = NULL;
    return new;
}

static void ft_lstadd_back_data(t_data **lst, t_data *new)
{
    if (!lst || !new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    t_data *tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

static char **extract_cmd_args(t_lexer *lex)
{
    int count = 0;
    t_lexer *tmp = lex;

    while (tmp)
    {
        if (tmp->type == REDIRE_IN || tmp->type == REDIRE_OUT || tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
        {
            tmp = tmp->next; 
            if (tmp && tmp->type == WORD)
                tmp = tmp->next;
            continue;
        }
        if (tmp->type == WORD)
            count++;
        tmp = tmp->next;
    }

    char **cmds = ft_malloc(sizeof(char *) * (count + 1));
    if (!cmds)
        return NULL;

    int i = 0;
    while (lex)
    {
        if (lex->type == REDIRE_IN || lex->type == REDIRE_OUT || lex->type == REDIR_APPEND || lex->type == HEREDOC)
        {
            lex = lex->next;
            if (lex && lex->type == WORD)
                lex = lex->next;
            continue;
        }
        if (lex->type == WORD)
            cmds[i++] = ft_strdup(lex->value);
        lex = lex->next;
    }
    cmds[i] = NULL;
    return cmds;
}

static void process_redirs_and_heredocs(t_lexer *lex, t_redir **redir, t_heredoc **heredoc)
{
    while (lex)
    {
        if ((lex->type == REDIRE_IN || lex->type == REDIRE_OUT || lex->type == REDIR_APPEND) &&
            lex->next && lex->next->type == FILEE)
        {
            t_redir *new = new_node_redir(ft_strdup(lex->next->value), lex->type);
            if (new)
                ft_lstadd_back_redir(redir, new);
            lex = lex->next;  // Skip filename token
        }
        else if (lex->type == HEREDOC && lex->next && lex->next->type == DELIMITER)
        {
            t_heredoc *new = new_node_heredoc(ft_strdup(lex->next->value));
            if (new)
                ft_lstadd_back_heredoc(heredoc, new);
            lex = lex->next;  
        }
        lex = lex->next;  
    }
}

int parse_commands(char *str, t_data **data)
{
    if (!d_quote(str, 0, 0, 0) || !check_pipe(str))
    {
        // g_es = 2;
        ft_putendl_fd("minishell~$ syntax error near unexpected", 2);
        return 1;
    }
    else
    {
        char **pipe_split = expand_and_split(str, NULL); //ls -a > as << as >> ls >> la| grep "amine" | wc -l
        if (!pipe_split)
            return 1;
        int i = 0;
        while (pipe_split[i])
        {
            char *new_line = fix_line(pipe_split[i]);
            char **args = ft_split_space(new_line);
            if (check_redirections(args) == 0)
            {
                ft_putendl_fd("minishell~$ syntax error near unexpected", 2);
                return 1;
            }
            if (!args)
            {
                i++;
                continue;
            }

            t_lexer *lex = ft_cmp(args);
            if (!lex)
            {
                // ft_free_2d(args);  // REMOVED - don't free tracked memory
                i++;
                continue;
            }

            char **cmds = extract_cmd_args(lex);
            if (!cmds)
            {
                free_lexer(lex);
                // ft_free_2d(args);  // REMOVED - don't free tracked memory
                i++;
                continue;
            }

            t_redir *redir = NULL;
            t_heredoc *heredoc = NULL;
            process_redirs_and_heredocs(lex, &redir, &heredoc);
        
            t_data *node = new_node_cmd(cmds);
            if (node)
            {
                node->redir = redir;
                node->herdoc = heredoc;
                ft_lstadd_back_data(data, node);
            }
            free_lexer(lex);
            // ft_free_2d(args);       // REMOVED - don't free tracked memory
            i++;
        }
        // ft_free_2d(pipe_split);    // REMOVED - don't free tracked memory
    }
    return 0;
}

void free_list(t_data *begin)
{
    // Don't free any tracked memory - ft_free_all() will handle it
    // This function now just serves to traverse and clean up the list structure
    
    t_data *tmp;
    while (begin)
    {
        tmp = begin;
        begin = begin->next;
        
        // Remove all free() calls for tracked memory:
        // - Don't free tmp->cmds[i] 
        // - Don't free tmp->cmds
        // - Don't free tmp itself
        
        // Only traverse the sublists to clean up pointers
        t_redir *r = tmp->redir;
        while (r)
        {
            t_redir *next = r->next;
            // Don't free r->filename or r
            r = next;
        }
        
        t_heredoc *h = tmp->herdoc;
        while (h)
        {
            t_heredoc *next = h->next;
            // Don't free h->delimeter or h
            h = next;
        }
    }
}
