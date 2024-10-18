/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:57:31 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/18 17:53:19 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_export(char *str)
{
	if (ft_strcmp(str, "export") == 0)
		return (1);
	return (0);
}

void	concat_export(t_shelly *shelly, char *str)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	char	*plus_equal_pos;

	plus_equal_pos = ft_strnstr(str, "+=", ft_strlen(str));
	*plus_equal_pos = '\0';
	key = ft_strdup(str);
	if (!key)
		return ;
	value = ft_strdup(plus_equal_pos + 2);
	if (!value)
		return ;
	tmp = shelly->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->content) == 0)
			return (update_existing_var(tmp, value), free(key), free(value));
		tmp = tmp->next;
	}
	add_new_env_var(shelly, key, value);
	free(key);
	free(value);
}

int	ft_export_2(t_shelly *shelly, char *av)
{
	if (ft_strnstr(av, "-", ft_strlen(av)) != NULL
		|| ft_strcmp(av, "+=") == 0
		|| ft_isdigit(av[0]) == 1 || av[0] == '=')
	{
		printf("bash: export: `%s': not a valid identifier\n", av);
		shelly->exit_code = 1;
		return (1);
	}
	return (0);
}

void	ft_export(t_shelly *shelly, char **av)
{
	int	i;

	if (shelly->env == NULL)
		initialize_default_env(shelly);
	i = 0;
	if (!av[1])
		affiche_export(shelly);
	while (av[++i])
	{
		if (ft_export_2(shelly, av[i]) == 1)
			return ;
	}
	i = 0;
	while (av[++i])
	{
		if (ft_strnstr(av[i], "+=", ft_strlen(av[i])))
			concat_export(shelly, av[i]);
		else if (av[i][0] != '-' || ft_strcmp(av[i], "+=") != 0)
			add_or_not(shelly, av[i]);
	}
}
