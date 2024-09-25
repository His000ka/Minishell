/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:01:25 by firdawssema       #+#    #+#             */
/*   Updated: 2024/09/17 18:35:22 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_builtins(t_shelly *shelly, char *cmd, t_ast *ast)
{
    if(if_cd(cmd))
	{
		printf("GG\n");
		return(ft_cd(ast->value), EXIT_SUCCESS);
	}
    if(if_echo(cmd))
        return(ft_echo(ast->value), EXIT_SUCCESS);
    if(if_env(cmd))
        return(ft_env(shelly->env), EXIT_SUCCESS);
    if(if_exit(ast->value))
        return(ft_exit(ast->value), EXIT_SUCCESS);
    // if(if_export(cmd))
    //     return(ft_exit(ast->value), EXIT_SUCCESS);
    if(if_pwd(cmd))
		return(ft_pwd(), EXIT_SUCCESS);
    // if(if_unset(cmd))
    //     return(ft_unset(env_list, ast->value), EXIT_SUCCESS);
    return(EXIT_FAILURE);
}
