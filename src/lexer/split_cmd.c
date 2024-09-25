/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:51 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/10 13:15:55 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_elem(t_shelly *shelly, int i, int res)
{
	int	s;

	s = 0;
	if (is_quote(&shelly->cmd[res], 1) != 0)
		return (i - res - 2);
	else if (is_good_char(&shelly->cmd[res], 1) != 0)
	{
		s = is_good_char(&shelly->cmd[res], 3);
		if (shelly->cmd[s] == 34
			|| shelly->cmd[s] == 39)
			return (i - res - 2);
		return (i - res);
	}
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

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
		dest[i] = '\0';
		i++;
	return (dest);
}

void	expender(t_shelly *shelly, t_data_elem *data)
{
	char	*var_value;
	char	*path;
	char	*test;
	int		size;
	int		start;

	start = data->k + data->i + 1;
	size = 0;
	path = NULL;
	shelly->str[data->j][data->k] = '\0';
	while (check_char(shelly->cmd[start + size]) == 0)
		size++;
	path = ft_strndup(&shelly->cmd[start], size);
	var_value = getenv(path);
	printf("path: %s\n", path);
	data->size = data->size - ft_strlen(path) + ft_strlen(var_value);
	printf("TMP: %d\n", data->size);
	free(path);
	if (var_value)
	{
		test = ft_strdup(shelly->str[data->j]);
		if (!test)
			printf("pas de test\n");
		printf("test: %s", test);
		free(shelly->str[data->j]);
		shelly->str[data->j] = malloc(sizeof(char) * data->size);
		if (!shelly->str[data->j])
			return ;
		int i = -1;
		while (++i < data->k)
			shelly->str[data->j][i] = test[i];
		while (*var_value)
		{
			shelly->str[data->j][data->k] = *var_value;
			data->k++;
			var_value++;
		}
		shelly->str[data->j][data->k] = '\0';
	}
	else
		data->k += size + 1;
	data->i =  size - data->k;
}

int	double_quote(t_shelly *shelly, t_data_elem *data)
{
	int	tmp;

	tmp = data->i;
	if (shelly->cmd[data->i] == 34)
	{
		while (shelly->cmd[data->i] != 34)
			data->i++;
		if (shelly->cmd[data->i] == '|' || shelly->cmd[data->i] == '>'
			|| shelly->cmd[data->i] == '<' || shelly->cmd[data->i] == ' ')
			return (1);
		else
		{
			while (data->k < data->size && shelly->cmd[data->k + tmp] != '\0')
			{
				if (shelly->cmd[data->k + tmp] != 34)
				{
					shelly->str[data->j][data->k] = shelly->cmd[data->k + tmp];
					data->k++;
				}
				else
					tmp++;
			}
			shelly->str[data->j][data->k] = '\0';
		}
		return (0);
	}
	return (1);
}

int	single_quote(t_shelly *shelly, t_data_elem *data)
{
	int	tmp;

	tmp = data->i;
	if (shelly->cmd[data->i] == 39)
	{
		while (shelly->cmd[data->i] != 39)
			data->i++;
		if (shelly->cmd[data->i] == '|' || shelly->cmd[data->i] == '>'
			|| shelly->cmd[data->i] == '<' || shelly->cmd[data->i] == ' ')
			return (1);
		else
		{
			while (data->k < data->size && shelly->cmd[data->k + tmp] != '\0')
			{
				if (shelly->cmd[data->k + tmp] != 39)
				{
					shelly->str[data->j][data->k] = shelly->cmd[data->k + tmp];
					data->k++;
				}
				else
					tmp++;
			}
			shelly->str[data->j][data->k] = '\0';
		}
		return (0);
	}
	return (1);
}

int	manage_quote(t_shelly *shelly, t_data_elem *data)
{
	int	check;

	check = 0;
	check += double_quote(shelly, data);
	check += single_quote(shelly, data);
	return (check);
}

void	manage_quote_v2(t_shelly *shelly, t_data_elem *data)
{
	if (shelly->cmd[data->k + data->i] == 34)
	{
		data->i++;
		while (shelly->cmd[data->k + data->i] != 34)
		{
			if (shelly->cmd[data->k + data->i] == '$')
					expender(shelly, data);
			else
				shelly->str[data->j][data->k] = shelly->cmd[data->k + data->i];
			data->k++;
			
		}
	}
	if (shelly->cmd[data->k + data->i] == 39)
	{
		data->i++;
		while (shelly->cmd[data->k + data->i] != 39)
		{
			shelly->str[data->j][data->k] = shelly->cmd[data->k + data->i];
			data->k++;
		}
	}
	data->i++;
}

int	add_elem(t_shelly *shelly, int count)
{
	t_data_elem	data;

	data.j = 0;
	while (data.j < count)
	{
		data.size = info_elem(shelly, data.j, "size");
		printf("size: %d\n", data.size);
		shelly->str[data.j] = malloc(sizeof(char) * (data.size + 1));
		if (!shelly->str[data.j])
			return (1);
		data.i = info_elem(shelly, data.j, "index");
		printf("i: %d\n", data.i);
		data.k = 0;
		// if (manage_quote(shelly, &data) != 0)
		// {
			while (data.k < data.size && shelly->cmd[data.k + data.i] != '\0')
			{
				if (shelly->cmd[data.k + data.i] == 34
					|| shelly->cmd[data.k + data.i] == 39)
						manage_quote_v2(shelly, &data);
				else if (shelly->cmd[data.k + data.i] == '$')
				{
					printf("avant: size %d\n i %d k %d\n", data.size, data.i, data.k);
					expender(shelly, &data);
					printf("apres: size %d\n i %d k %d\n", data.size, data.i, data.k);
				}
				else
				{
					shelly->str[data.j][data.k] = shelly->cmd[data.k + data.i];
					data.k++;
				}
			}
			shelly->str[data.j][data.k] = '\0';
		// }
		data.j++;
	}
	shelly->str[data.j] = NULL;
	return (0);
}

int	split_command(t_shelly *shelly)
{
	int	count;

	count = 0;
	count += count_elem(shelly, count);
	printf("count : %d\n", count);
	if (count == 0)
		return (1);
	// if (count == 1)
	// {
	// 	printf("test");
	// 	return (1);
	// }
	shelly->str = malloc(sizeof(char *) * (count + 1));
	if (!shelly->str)
		return (1);
	if (add_elem(shelly, count) == 1)
		return (1);
	return (0);
}
