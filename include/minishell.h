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
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

//token
# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

//MSG_ERROR
# define SYNTAX_ERROR	"bash: syntax error near unexpected token ''\n"

//variable environnement

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
	char	**str;
	int		loop;
	t_env	*env;
	t_token	*token;
}	t_shelly;

//utils
int		ft_error(char *str, char var, int nb);
char	*ft_strndup(const char *s, int n);
char	*ft_strsearch(char *s, int c, int flag);

//parse
int		ft_parse(t_shelly *shelly);

//split_cmd
int		size_elem(t_shelly *shelly, int i, int res);
int		browse_elem(t_shelly *shelly, int i, int res);
int		info_elem(t_shelly *shelly, int j, char *str);
void	add_elem(t_shelly *shelly, int count);
void	split_command(t_shelly *shelly);

//init
int		init_shelly(t_shelly *shelly);
int		init_env(char **envp, t_env *env);

//check
int		check_quote(t_shelly *shelly);
int		check_last_elem(t_shelly *shelly);
int		check_cmd(t_shelly *shelly);

//free
void	free_envp(t_env *env);
void	ft_free(t_shelly *shelly);
void	ft_free_token(t_token *t);

//token
// int		is_pipe(char c);

//count_elem
int		count_index(char *str, int flag);
int		check_char(char c);
int		count_elem(t_shelly *shelly, int count);

//count_elem2
int		is_quote(char *str, int flag);
int		is_good_char(char *str, int flag);
int		is_pipe(char *str, int flag);
int		is_trunc(char *str, int flag);
int		is_input(char *str, int flag);

//affiche
void	affiche_elem(t_shelly *shelly);
void	affiche_token(t_shelly *shelly);
void	affiche_env_list(t_env *list);

//built-in
//cd
int 	if_cd(char *str);
void	ft_cd(char **str);
char	*ft_strjoin_pwd(char const *s1, char const *s2);
//echo
int		if_echo(char *str);
void	ft_echo(char **str);
//env
int		if_env(char *str);
void	ft_env(t_env *env_list);
//exit
int		if_exit(char *str);
int		is_numeric(char *str);
int		ft_exit(char **str);
//export
int		if_export(char *str);
void	ft_export(t_env *list_env);
//pwd
int		if_pwd(char *str);
void	ft_pwd(void);
//unset
int	if_unset(char *str);
void ft_unset(t_env *env_list, char **str);
//env_list
t_env	*create_env_node(char *env_var);
void	add_node_env(t_env **list, t_env *new);
t_env	*create_env_list(t_env **list, char **envp);
//control
void	control();
void control_c(int sig);
void	control_d();

#endif