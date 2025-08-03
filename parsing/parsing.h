/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:29:34 by w                 #+#    #+#             */
/*   Updated: 2025/08/02 11:55:22 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// Forward declarations
typedef struct s_lexer t_lexer;
typedef struct s_redirections t_redir;
typedef struct s_heredoc t_heredoc;

typedef enum s_type
{
    WORD,
    PIPE,
    REDIRE_IN,
    REDIRE_OUT,
    REDIR_APPEND,
    HEREDOC,
    FILEE,
    DELIMITER,
    NOTDEF
} t_type;

typedef struct s_lexer
{
    t_type type;
    char *value;
    t_lexer *next;    
    // struct s_lexer *prev;
}   t_lexer;
//t_lexer *head, head->type = REDIRE_IN;
typedef struct s_redirections
{
    char *filename;//smiya dyal file
    t_type type;//REIR IN OUT APPEND type dyal token li l9itit
    t_redir *next;//next file ila kan
}   t_redir;

typedef struct s_heredoc
{
    char *delimeter;
    t_heredoc *next;
} t_heredoc;

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;


typedef struct s_cmd
{
    char *value;
    struct s_cmd *next;
}   t_cmd_lst;

typedef struct s_data
{
    char    **cmds;//ls, -la, zft ,|, wc ,-l,NULL
    t_redir *redir;
    t_heredoc *herdoc;
    char **envp;
    t_env *env;
    struct  s_data *next; //create new node
}   t_data;

/*

int	add_addr(t_general *ctx, t_memory *new_addr)
{
	t_memory	*tmp;

	if (!new_addr)
	{
		cleanup(ctx);
		return (0);
	}
	if (!ctx->heap)
	{
		ctx->heap = new_addr;
		return (1);
	}
	tmp = ctx->heap;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_addr;
	return (1);
}

t_memory	*new_addr(void *ptr)
{
	t_memory	*node;

	node = malloc(sizeof(t_memory));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}
*/
//leaks

typedef struct s_save
{
	void *add;
	struct s_save *next;
}	t_save;

// newaddr()
// {
//     //allocate new node 
//     /*
//     *   MALLOC *s
//         gad t_heap node
        // heap>ptr  = s;    
    // ?*/
// }

char **ft_split_cmd(const char *s);
t_data *new_node(char **args);
void ft_lstadd_back2(t_data **lst, t_data *new);
void free_list(t_data *begin);

t_redir *new_node_redir(char *file,t_type type);
t_redir	*ft_lstlast_redir(t_redir *lst);
void ft_lstadd_back_redir(t_redir **lst, t_redir *new);

t_lexer *ft_cmp(char **av);
int count_lex(t_lexer *lex, t_type type);
t_lexer *new_node_lexer(char *args,t_type type);
t_lexer	*ft_lstlast_lexer(t_lexer *lst);
void ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);

t_heredoc *new_node_heredoc(char *dlm);
t_heredoc *ft_lstlast_heredoc(t_heredoc *lst);
void ft_lstadd_back_heredoc(t_heredoc **lst, t_heredoc *new);


void ft_free_2d(char **arr);
int parse_commands(char *str, t_data **data);
// void parse_commands(char *str, t_data **data, t_redir **redir, t_heredoc **heredoc);

t_env *init_env_list(char **envp);
int    builtin_env(t_data *min);

int ft_strcmp(char *s1, char *s2);
void remove_variable(t_env **env, char *to_remove);
int echo_command(t_data *data);
int built_cd(t_data *data);
int    get_pwd(t_data *data);
int builtin_unset(char **args, t_env **env_list);
//int execution(t_data *data, t_env *env,char **envp);
int execute_command(t_data *data, t_env *env);
void int_handler(int status) ;
int	count_env_vars(t_env *env);
void	free_partial_envp(char **envp, int i);
char *get_enviroment(t_env *env, char *key);
char	*is_direct_path_or_null(char *cmd, t_env *env);
char	*search_in_paths(char **paths, char *cmd);
char	*join_key_value(t_env *tmp);
char	*join_key_value(t_env *tmp);
int	setup_heredoc_pipe(t_heredoc *heredoc, int *pipefd, pid_t *pid);
void	run_heredoc_child(t_heredoc *heredoc, int write_fd);
int is_builtin(char *cmd);
int is_child_safe_builtin(char *cmd);
int is_parent_builtin(char *cmd);
int is_redirection(t_redir *current_redir, int has_input_redir, int has_output_redir);
int apply_redirection(t_redir *current_redir, int *has_input_redir, int *has_output_redir);
void ft_free_2d(char **arr);
int skip_spaces(const char *input, int i);
int open_redir_file(t_redir *redir);
void run_heredoc_child(t_heredoc *heredoc, int write_fd);
//test
char	**expand_and_split(char *line, char **info);
char    *expand_line(char *line, int dquote, char *plus, char **info);
int     skip_quotes(char *line, int i, int *dquote);
char    *ft_strjoin1(char const *s1, char const *s2);
int     handle_dollar(char **plus, char *line, char **info);
char    *expand_val(char *s, char **info);
char    *handle_dollar_case(char *start);
char    *find_end(char *start);

int	check_split(char *line, int i, char q);
int	d_quote(char *line, int dquote, int quote, int i);
int	check_pipe(char *line);
int	if_check_pipe(char *line, int i, char q);
char	*qoute_remov(char *line, char q, int i, int l);
int	is_pipe_syntax_error(char *line, int i);
char	*fix_line(char *line);
int	check_redirections(char **p_line);
char	**ft_split_space(const char *s);
int	is_quote(char c);
int	skip_quote(const char *s, int i);
//anti_leaks
t_save	**save_add(void);
void	*ft_malloc(size_t size);
void	ft_free_all(void);


#endif
