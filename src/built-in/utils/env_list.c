/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:00:37 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 10:42:34 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strsearch(char *s, int c, int flag)
{
	int	i;
	char *tmp;

	i = 0;
	while (c >= 256)
		c -= 256;
	while (s[i] != '\0')
	{
		if (s[i] == c && flag == 0)
			return (&s[i + 1]);
		else  if(s[i] == c && flag == 1)
			return(ft_strndup(s, i));
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

t_env	*create_env_node(char *env_var)
{
	t_env	*new;
	char *content;
	char *value;
	int i;

	i = 0;
	
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
		new->content = ft_strsearch(env_var, '=', 1);
		new->value = ft_strsearch(env_var, '=', 0);
		if(new->value != NULL)
			new->type = 1;
		else
			new->type = 0;
		new->next = NULL;
		i++;
	return (new);
}

void	add_node_env(t_env **list, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (*list == NULL)
	{
		*list = new;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*create_env_list(t_env **list, char **envp)
{
	t_env	*new;
	int i = 0;

	while (envp[i])
	{
		new = create_env_node(envp[i]);
		add_node_env(list, new);
		i++;
	}
	return (*list);
}

void	print_env_list(t_env *list)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("Content: %s\n", tmp->content);
		printf("Value: %s\n", tmp->value);
		tmp = tmp->next;
	}
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env_list;

// 	(void)ac;
// 	(void)av;
// 	env_list = NULL;
// 	env_list = create_env_list(&env_list, envp);

// 	print_env_list(env_list);

// 	int i = 0;
// 	while(envp[i])
// 	{
// 			printf("%s\n" , envp[i]);
// 			i++;
// 	}

// 	return (0);
// }
