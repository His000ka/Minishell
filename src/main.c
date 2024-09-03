/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:02:29 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/03 16:37:09 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	t_shelly	shelly;
	while (1)
	{
		shelly.cmd = readline("bash> ");
		if (!shelly.cmd)
			shelly.loop = ft_error("Error launching shell");
		// printf("%s\n", shelly.cmd);
		add_history(shelly.cmd);
		ft_parse(&shelly);
		//shelly.loop = ft_error("Error launching shell");
		free(shelly.cmd);
	}
}
