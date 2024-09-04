/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:00:19 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/04 14:27:10 by pitroin          ###   ########.fr       */
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

//variable environnement
typedef struct s_env
{
	char	**envp;
}	t_env;

//token
typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

//struct principale
typedef struct	s_shelly
{
	char	*cmd;
	char	**str;
	int		loop;
	t_env	*env;
	t_token	*token;
}	t_shelly;

int		ft_error(char *str, t_shelly *shelly);
int		ft_parse(t_shelly *shelly);
//init
int		init_shelly(char **envp, t_shelly *shelly);
int		init_env(char **envp, t_env *env);

//free
void	free_envp(t_env *env);
void	ft_free(t_shelly *shelly);

#endif