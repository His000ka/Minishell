/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:57:31 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/16 13:34:00 by firdawssema      ###   ########.fr       */
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
	if (!plus_equal_pos)
		return ;
	*plus_equal_pos = '\0';
	key = ft_strdup(str);
	value = ft_strdup(plus_equal_pos + 2);
	tmp = shelly->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->content) == 0)
		{
			update_existing_var(tmp, value);
			free(key);
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_new_env_var(shelly, key, value);
	free(key);
	free(value);
}

void	ft_export(t_shelly *shelly, char **av)
{
	int	i;

	i = 1;
	if (!av[1])
		affiche_export(shelly);
	while (av[i])
	{
		if (av[i][0] == '-' || ft_strcmp(av[i], "+=") == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n", av[i]);
			return ;
		}
		i++;
	}
	i = 1;
	while (av[i])
	{
		if (ft_strnstr(av[i], "+=", ft_strlen(av[i])))
			concat_export(shelly, av[i]);
		else if (av[i][0] != '-' || ft_strcmp(av[i], "+=") != 0)
			add_or_not(shelly, av[i]);
		else
			printf("bash: export: `%s': not a valid identifier\n", av[i]);
		i++;
	}
}
