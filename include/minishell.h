/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:00:19 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/09 18:23:22 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_shelly
{
	char			*cmd;
	int				loop;
}					t_shelly;

typedef struct s_env
{
	char			*content;
	char			*value;
	int				type;
	struct s_env	*next;

}					t_env;

int					ft_error(char *str);
t_env	*create_env_list(t_env **list, char **envp);
void	add_node_env(t_env **list, t_env *new);
t_env	*create_env_node(char *envp);

#endif