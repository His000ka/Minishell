/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:58:59 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/04 12:02:42 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_trunc(t_shelly *shelly, t_ast *node)
{
    int     fd_out;
    pid_t   pid;

    if (node->right->node_type != CMD)
        ft_exec(shelly, node->right);
    fd_out = open(search_value(node), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        perror("ERROR OPEN");
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            perror("ERROR DUP2");
            exit(EXIT_FAILURE);
        }
        close(fd_out);
		if (node->left)
        	ft_exec(shelly, node->left);
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0)
    {
        close(fd_out);
        waitpid(pid, NULL, 0);
    }
    else
    {
        perror("ERROR FORK");
        exit(EXIT_FAILURE);
    }
}
