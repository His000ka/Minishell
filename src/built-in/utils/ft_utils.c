/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:20 by fimazouz			       #+#    #+#     */
/*   Updated: 2024/10/18 01:03:45 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin_pwd(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (p == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		p[i] = s1[i];
	p[++i] = '/';
	j = -1;
	while (s2[++j] != '\0')
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}

void	swap_env(t_env *a, t_env *b)
{
	char	*temp_content;
	char	*temp_value;
	int		temp_type;

	temp_content = a->content;
	temp_value = a->value;
	temp_type = a->type;
	a->content = b->content;
	a->value = b->value;
	a->type = b->type;
	b->content = temp_content;
	b->value = temp_value;
	b->type = temp_type;
}

void	sort_env_list(t_env *env_list)
{
	t_env	*current;
	t_env	*next;
	int		sorted;

	if (!env_list)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = env_list;
		while (current->next != NULL)
		{
			next = current->next;
			if (ft_strcmp(current->content, next->content) > 0)
			{
				swap_env(current, next);
				sorted = 0;
			}
			current = current->next;
		}
	}
}
