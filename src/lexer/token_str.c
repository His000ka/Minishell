/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:12:11 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/22 11:43:30 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*not_special_token(t_data_elem *data, char *val)
{
	char		*tmp;

	data->size = 0;
	while (val[data->i + data->size] != '$' && val[data->i + data->size] != '\''
		&& val[data->i + data->size] != '\"'
		&& val[data->i + data->size] != '\0')
		data->size++;
	tmp = ft_strndup(&val[data->i], data->size);
	data->i += data->size;
	return (tmp);
}

char	*if_res(char *res, char *tmp1, char *tmp2)
{
	char	*res2;

	res2 = ft_strdup(res);
	free(res);
	if (!tmp2)
		res = ft_strjoin(res2, tmp1);
	else
		res = ft_strjoin(ft_strjoin(res2, tmp1), tmp2);
	free(res2);
	return (res);
}

char	*token_str_2(char *val, t_data_elem *data, t_shelly *shelly)
{
	char	*tmp2;

	tmp2 = NULL;
	if (val[data->i] == 34 || val[data->i] == 39)
		tmp2 = manage_quote(shelly, data, val);
	else if (val[data->i] == '$')
		tmp2 = expender(shelly, data, val, 1);
	return (tmp2);
}

int	ft_search_heredoc(t_shelly *shelly)
{
	t_token	*prev;

	prev = shelly->token;
	if (!prev)
		return (0);
	while (prev->next != NULL)
		prev = prev->next;
	if (prev->type == HEREDOC)
		return (1);
	return (0);
}

char	*token_str(t_shelly *shelly, char *val)
{
	t_data_elem	data;
	char		*tmp1;
	char		*tmp2;
	char		*res;

	data.i = 0;
	res = NULL;
	if ((ft_strchr(val, '$') == NULL && ft_strchr(val, '\'') == NULL
			&& ft_strchr(val, '\"') == NULL) || (ft_search_heredoc(shelly) == 1
			&& ft_strchr(val, '\'') == NULL && ft_strchr(val, '\"') == NULL))
		return (ft_strdup(val));
	while (val[data.i] != '\0')
	{
		tmp1 = not_special_token(&data, val);
		tmp2 = token_str_2(val, &data, shelly);
		if (res)
			res = if_res(res, tmp1, tmp2);
		else
			res = ft_strjoin(tmp1, tmp2);
		ft_free_tmp(&tmp1, &tmp2);
		if (val[data.i] != '\0' && val[data.i] != '$')
			data.i++;
	}
	return (res);
}
