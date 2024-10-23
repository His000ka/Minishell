/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:10:52 by marvin            #+#    #+#             */
/*   Updated: 2024/10/23 10:29:29 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*before_expend(char *input, t_data_elem *data)
{
	char	*tmp;

	data->size = 0;
	while (input[data->size] != '$' && input[data->size] != '\0')
		data->size++;
	tmp = ft_strndup(input, data->size);
	data->i += data->size;
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*expend_heredoc(t_shelly *shelly, char *input)
{
	char		*expend;
	char		*res;
	t_data_elem	data;

	data.i = 0;
	if (ft_strchr(input, '$') == NULL)
		return (ft_strdup(input));
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (input[data.i] != '\0')
	{
		if (input[data.i] == '$')
			expend = ft_strjoin(res, expender(shelly, &data, input));
		else
			expend = ft_strjoin(res, before_expend(input, &data));
		free(res);
		res = ft_strdup(expend);
		free(expend);
		expend = NULL;
	}
	return (res);
}

void	read_heredoc(t_shelly *shelly)
{
	char		*input;
	char		*expend;

	while (1)
	{
		input = readline("Heredoc>");
		if (ft_strcmp(input, shelly->delimiter) == 0)
		{
			free(input);
			break ;
		}
		expend = expend_heredoc(shelly, input);
		if (expend)
		{
			write(shelly->fd[1], expend, ft_strlen(expend));
			write(shelly->fd[1], "\n", 1);
			free(expend);
		}
		free(input);
	}
}

int	adapt_cmd(t_shelly *shelly)
{
	t_token	*current;
	t_token	*tmp;

	current = shelly->token;
	while (current && current->type != HEREDOC)
		current = current->next;
	if (!current)
		return (0);
	tmp = current->next;
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	ft_free_heredock(shelly, tmp, current);
	affiche_token(shelly);
	if (ft_parser(shelly) == 0)
	{
		if (exec_heredoc(shelly, shelly->ast) == 0)
			ft_exec(shelly, shelly->ast);
	}
	return (0);
}

void	exec_fork_heredoc(t_shelly *shelly, t_ast *node)
{
	pid_t	pid;
	int		fd_in;

	fd_in = shelly->fd[0];
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			write(STDERR_FILENO, "ERROR DUP2\n", 11);
			exit(EXIT_FAILURE);
		}
		close(fd_in);
		if (node->left)
			ft_exec(shelly, node->left);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(fd_in);
		waitpid(pid, NULL, 0);
	}
	else
		write(STDERR_FILENO, "ERROR FORK\n", 11);
}
