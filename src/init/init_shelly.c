/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shelly.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:45:25 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 11:51:42 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int init_shelly(t_shelly *shelly)
{
    shelly->str = NULL;
    shelly->token = NULL;
    shelly->cmd = NULL;
    shelly->ast = NULL;
	shelly->delimiter = NULL;
	shelly->exit_status = ft_strdup("0");
	if (!shelly->exit_status)
		return (1);
    return (0);
}
