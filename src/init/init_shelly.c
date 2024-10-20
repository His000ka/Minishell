/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shelly.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:00:50 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/08 20:00:50 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_shelly(t_shelly *shelly)
{
	shelly->str = NULL;
	shelly->token = NULL;
	shelly->cmd = NULL;
	shelly->ast = NULL;
	shelly->delimiter = NULL;
	shelly->exit_code = 0;
	return (0);
}
