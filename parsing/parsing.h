/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:29:34 by w                 #+#    #+#             */
/*   Updated: 2025/08/07 22:52:26 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
// Forward declarations
typedef struct s_lexer			t_lexer;
typedef struct s_redirections	t_redir;
typedef struct s_heredoc		t_heredoc;

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
}								t_type;

typedef struct s_lexer
{
	t_type						type;
	char						*value;
	t_lexer						*next;
}								t_lexer;

typedef struct s_redirections
{
	char						*filename;
	t_type						type;
	t_redir						*next;
}								t_redir;

typedef struct s_heredoc
{
	char						*delimeter;
	t_heredoc					*next;
}								t_heredoc;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_cmd
{
	char						*value;
	struct s_cmd				*next;
}								t_cmd_lst;

typedef struct s_data
{
	char						**cmds;
	t_redir						*redir;
	t_heredoc					*herdoc;
	char						**envp;
	t_env						*env;
	struct s_data				*next;
}								t_data;

typedef struct s_save
{
	void						*add;
	struct s_save				*next;
}								t_save;

char							**ft_split_cmd(const char *s);
void							free_list(t_data *begin);
void							ft_lstadd_back_redir(t_redir **lst,
									t_redir *new);
int								count_lex(t_lexer *lex, t_type type);
void							ft_lstadd_back2(t_data **lst, t_data *new);
void							ft_lstadd_back_lexer(t_lexer **lst,
									t_lexer *new);
t_redir							*new_node_redir(char *file, t_type type);
t_redir							*ft_lstlast_redir(t_redir *lst);
t_data							*new_node(char **args);
t_lexer							*ft_cmp(char **av);
t_lexer							*new_node_lexer(char *args, t_type type);
t_lexer							*ft_lstlast_lexer(t_lexer *lst);
t_heredoc						*new_node_heredoc(char *dlm);
t_heredoc						*ft_lstlast_heredoc(t_heredoc *lst);
void							ft_lstadd_back_heredoc(t_heredoc **lst,
									t_heredoc *new);
void							ft_free_2d(char **arr);
int								parse_commands(char *str, t_data **data);
t_env							*init_env_list(char **envp);
int								builtin_env(t_data *min);
int								ft_strcmp(char *s1, char *s2);
void							remove_variable(t_env **env, char *to_remove);
int								echo_command(t_data *data);
int								built_cd(t_data *data);
int								get_pwd(t_data *data);
int								builtin_unset(char **args, t_env **env_list);
int								execute_command(t_data *data, t_env *env);
void							int_handler(int status);
int								count_env_vars(t_env *env);
void							free_partial_envp(char **envp, int i);
char							*get_enviroment(t_env *env, char *key);
char							*is_direct_path_or_null(char *cmd, t_env *env);
char							*search_in_paths(char **paths, char *cmd);
char							*join_key_value(t_env *tmp);
char							*join_key_value(t_env *tmp);
int								setup_heredoc_pipe(t_heredoc *heredoc,
									int *pipefd, pid_t *pid);
void							run_heredoc_child(t_heredoc *heredoc,
									int write_fd);
int								is_builtin(char *cmd);
int								is_child_safe_builtin(char *cmd);
int								is_parent_builtin(char *cmd);
int								is_redirection(t_redir *current_redir,
									int has_input_redir, int has_output_redir);
int								apply_redirection(t_redir *current_redir,
									int *has_input_redir,
									int *has_output_redir);
void							ft_free_2d(char **arr);
int								skip_spaces(const char *input, int i);
int								open_redir_file(t_redir *redir);
void							run_heredoc_child(t_heredoc *heredoc,
									int write_fd);
//test
char							**expand_and_split(char *line, char **info);
char							*expand_line(char *line, int dquote, char *plus,
									char **info);
int								skip_quotes(char *line, int i, int *dquote);
char							*ft_strjoin1(char const *s1, char const *s2);
int								handle_dollar(char **plus, char *line,
									char **info);
char							*expand_val(char *s, char **info);
char							*handle_dollar_case(char *start);
char							*find_end(char *start);

int								check_split(char *line, int i, char q);
int								d_quote(char *line, int dquote, int quote,
									int i);
int								check_pipe(char *line);
int								if_check_pipe(char *line, int i, char q);
char							*qoute_remov(char *line, char q, int i, int l);
int								is_pipe_syntax_error(char *line, int i);
char							*fix_line(char *line);
int								check_redirections(char **p_line);
char							**ft_split_space(const char *s);
int								is_quote(char c);
int								skip_quote(const char *s, int i);
//anti_leaks
t_save							**save_add(void);
void							*ft_malloc(size_t size);
t_data							*new_node_cmd(char **cmds);
void							ft_free_all(void);
void							ft_lstadd_back_data(t_data **lst, t_data *new);
char							*expand_line1(char *line,
									char *plus, char **info);
char							**extract_cmd_args(t_lexer *lex);
void							handle_heredoc_p(char **av, int *i, t_lexer **tokens);
void							handle_input(char **av, int *i, t_lexer **tokens);
void							handle_output(char **av, int *i, t_lexer **tokens);
void							handle_append(char **av, int *i, t_lexer **tokens);
int								handle_heredoc(t_heredoc *heredoc);



#endif
