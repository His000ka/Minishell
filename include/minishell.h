/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:00:19 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 12:48:18 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

//token
# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"
# define MINISHELL	8	//"./minishell"

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

//MSG_ERROR
# define SYNTAX_ERROR	"bash: syntax error near unexpected token ''\n"
# define SYNTAX_TOKEN	"bash: syntax error near unexpected token 'newline'\n"

typedef struct s_data_elem
{
	int	k;
	int	i;
	int	size;
	int	j;
}				t_data_elem;

//variable environnement
typedef struct s_ast
{
	char			**value;
	int				node_type;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_env
{
	char			*content;
	char			*value;
	int				type;
	struct s_env	*next;
}					t_env;

//token
typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

//struct principale
typedef struct s_shelly
{
	char	*cmd;
	int		ctrlc;
	int		ctrls;
	int		oldpwd_count;
	int		process_running;
	char	**str;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		loop;
	char	*delimiter;
	int		fd[2];
	int		exit_code;
	t_env	*env;
	t_token	*token;
	t_ast	*ast;
}	t_shelly;

// shelly
t_shelly	*get_shelly(void);
//algo_shelly
void		algo_minishell(t_shelly *shelly);
//utils
int			ft_error(char *str, char var, int nb);
char		*ft_strndup(const char *s, int n);
char		*ft_strsearch(char *s, int c, int flag);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strtok(char *str, const char *delim);
void		recup_value_1(t_ast *node);
//msg_error
void		msg_not_file(t_shelly *shelly, char *value);
void		msg_cmd_not_found(t_ast *node);
//lexer
int			ft_lexer(t_shelly *shelly);
//tokenstr
char		*token_str(t_shelly *shelly, char *val);
void		ft_free_tmp(char **tmp1, char **tmp2);
//parser
int			ft_parser(t_shelly *shelly);
int			is_cmd(int type);
//check mult
int			check_mult_token(t_shelly *shelly, t_token *token);
//exec
void		pid_pos(t_shelly *shelly, int fd_out, pid_t pid);
void		*ft_exec(t_shelly *shelly, t_ast *node);
char		*search_value(t_ast *node);
//execve
void		exit_code_execve(t_shelly *shelly);
int			exec_cmd_path(char *cmd, char **args, t_shelly *shelly);
char		*find_executable_in_path(t_shelly *shelly, char *cmd);
//ast
t_ast		*create_ast(t_token *tokens);
t_ast		*create_ast_node(char **value, int node_type);
char		**extract_command(t_token *token);
int			count_command_tokens(t_token *token);
//ast 2
t_ast		*buid_left_pipe(t_token *tokens);
t_ast		*ast_heredoc(t_token *tokens, t_ast *root);
t_ast		*ast_pipe(t_token *tokens, t_ast *root);
t_ast		*ast_priority(t_token *tokens, t_ast *root);
//exec heredoc
int			exec_heredoc(t_shelly *shelly, t_ast *node);
int			exec_heredoc_2(t_shelly *shelly, t_ast *node);
void		read_heredoc(t_shelly *shelly);
char		*search_delimiter(t_ast *node);
int			search_heredoc(t_shelly *shelly, t_ast *node);
void		exec_fork_heredoc(t_shelly *shelly, t_ast *node);
int			adapt_cmd(t_shelly *shelly);
void		ft_free_heredock(t_shelly *shelly, t_token *current, t_token *tmp);
char		*search_delimiter(t_ast *node);
//exec trunc
void		exec_trunc(t_shelly *shelly, t_ast *node);
void		exec_trunc_2(t_shelly *shelly, t_ast *node, t_ast *node_in);
//exec append
void		exec_append(t_shelly *shelly, t_ast *node);
//exec input
void		exec_input(t_shelly *shelly, t_ast *node);
//pipe
void		exec_pipe(t_shelly *shelly, t_ast *node);
void		handle_pipe_error(void);
void		handle_fork_error(void);
void		child_process_left(t_shelly *shelly, t_ast *node, int pipe_fd[2]);
void		child_process_right(t_shelly *shelly, t_ast *node, int pipe_fd[2]);
void		exec_pipe(t_shelly *shelly, t_ast *node);
void		status_pipe(pid_t pid1, pid_t pid2, t_shelly *shelly);
//split_cmd
int			size_elem(t_shelly *shelly, int i, int res);
int			browse_elem(t_shelly *shelly, int i, int res);
int			info_elem(t_shelly *shelly, int j, char *str);
int			add_elem(t_shelly *shelly, int count);
int			split_command(t_shelly *shelly);
//init
int			init_shelly(t_shelly *shelly, char **envp);
//quote utils (lexer)
int			check_quote(t_shelly *shelly);
char		*manage_quote(t_shelly *shelly, t_data_elem *data, char *val);
//info_elem (lexer)
int			info_elem(t_shelly *shelly, int j, char *str);
//free
void		free_env(t_shelly *shelly);
void		ft_free(t_shelly *shelly);
void		free_ast(t_ast *node);
//expender
char		*expender(t_shelly *shelly, t_data_elem *data, char *val);
//count_elem
int			count_index(char *str, int flag);
int			check_char(char c);
int			count_elem(t_shelly *shelly, int count);
//count_elem2
int			is_quote(char *str, int flag);
int			is_good_char(char *str, int flag);
int			is_pipe(char *str, int flag);
int			is_trunc(char *str, int flag);
int			is_input(char *str, int flag);
//affiche
void		affiche_elem(t_shelly *shelly);
void		affiche_token(t_shelly *shelly);
void		affiche_env_list(t_env *list);
void		affiche_ast(t_ast *node, int level);
//built-in
int			ft_builtins(t_shelly *shelly, char *cmd, t_ast *ast);
int			ft_strcmp(const char *s1, const char *s2);
int			is_valid_identifier(char *str);
void		sort_env_list(t_env *env_list);
void		swap_env(t_env *a, t_env *b);
//cd
int			if_cd(char *str);
void		ft_cd(char **str);
char		*ft_strjoin_pwd(char const *s1, char const *s2);
//echo
int			if_echo(char *str);
void		ft_echo(char **str);
//env
int			if_env(char *str);
void		ft_env(t_shelly *shelly);
char		*ft_strjoin_free(char *s1, char const *s2);
void		initialize_default_env(t_shelly *shelly);
void		update_envp(t_shelly *shelly);
void		copy_env_to_envp(t_shelly *shelly);
void		free_envp(char **envp);
int			count_env_vars(t_env *env);
char		*get_value_env(t_shelly *shelly, char *path);
//exit
int			if_exit(char **str);
int			is_numeric(char *str);
int			ft_exit(char **str);
//export
int			if_export(char *str);
void		ft_export(t_shelly *shelly, char **av);
void		affiche_export(t_shelly *shelly);
void		add_node_export(t_env *list, t_env *new);
void		add_or_not(t_shelly *shelly, char *str);
void		update_existing_var(t_env *tmp, char *value);
void		add_new_env_var(t_shelly *shelly, char *key, char *value);
void		concat_export(t_shelly *shelly, char *str);
//pwd
int			if_pwd(char *str);
void		ft_pwd(char **str);
//unset
int			if_unset(char *str);
void		ft_unset(t_env **env_list, char **args);
//env_list
t_env		*create_env_node(char *env_var);
void		add_node_env(t_env **list, t_env *new);
int			create_env_list(t_shelly *shelly, char **envp);
//control
void		control(void);
void		control_d(void);
void		control_c(int sig);
#endif