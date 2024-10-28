/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:06:34 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/21 18:17:02 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_elem(t_shelly *shelly, int i, int res)
{
	if (is_quote(&shelly->cmd[res], 1) != 0)
		return (i - res);
	else if (is_good_char(&shelly->cmd[res], 1) != 0)
		return (i - res);
	return (1);
}

int	browse_elem(t_shelly *shelly, int i, int res)
{
	i += is_quote(&shelly->cmd[i], 1);
	if (i == res)
		i += is_good_char(&shelly->cmd[i], 2);
	if (i == res)
		i += is_pipe(&shelly->cmd[i], 1);
	if (i == res)
		i += is_input(&shelly->cmd[i], 1);
	if (i == res)
		i += is_trunc(&shelly->cmd[i], 1);
	return (i);
}

int	info_elem(t_shelly *shelly, int j, char *str)
{
	int	i;
	int	res;
	int	count;

	i = 0;
	count = -1;
	while (++count <= j && shelly->cmd[i] != '\0')
	{
		i += count_index(&shelly->cmd[i], 1);
		res = i;
		i = browse_elem(shelly, i, res);
	}
	if (ft_strncmp(str, "index", 6) == 0)
		return (res);
	else if (ft_strncmp(str, "size", 4) == 0)
		return (size_elem(shelly, i, res));
	return (0);
}
