/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:24:30 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/22 14:31:12 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_env(char *str)
{
	if (ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (result);
}

void	initialize_default_env(t_shelly *shelly)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		add_new_env_var(shelly, ft_strdup("PWD"), ft_strdup(cwd));
	add_new_env_var(shelly, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	update_envp(shelly);
}

void	ft_env(t_shelly *shelly)
{
	t_env	*tmp;

	if (shelly->env == NULL)
		initialize_default_env(shelly);
	if (get_value_env(shelly, "PATH") == NULL
		|| ft_strcmp(get_value_env(shelly, "PATH"), getenv("PATH")))
	{
		msg_not_file(shelly, "env");
		return ;
	}
	tmp = shelly->env;
	while (tmp != NULL)
	{
		if (tmp->type == 1 && tmp->value != NULL && tmp->value[0] != '\0')
			printf("%s=%s\n", tmp->content, tmp->value);
		tmp = tmp->next;
	}
}
