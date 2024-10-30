/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:37:12 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/30 16:51:51 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	remove_token_links(t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
}

static t_token	*skip_pipe(t_token *tmp)
{
	if (tmp->next && tmp->next->type == PIPE)
	{
		tmp = tmp->next;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	return (tmp);
}

static t_token	*process_heredoc(t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	remove_token_links(current);
	remove_token_links(tmp);
	return (skip_pipe(tmp));
}

int	adapt_cmd(t_shelly *shelly)
{
	t_token	*current;
	t_token	*tmp;

	current = shelly->token;
	while (current && current->type != HEREDOC)
		current = current->next;
	if (!current || !current->next)
		return (0);
	tmp = process_heredoc(current);
	ft_free_heredock(shelly, tmp, current);
	if (ft_parser(shelly) == 0 && exec_heredoc(shelly, shelly->ast) == 0)
		ft_exec(shelly, shelly->ast);
	return (0);
}
