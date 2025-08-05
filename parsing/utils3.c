/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:41:42 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/04 22:28:12 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_quotes(char *line, char *new_line, int *i, int *l)
{
	char	q;

	q = line[*i];
	new_line[(*l)++] = line[(*i)++];
	while (line[*i] && line[*i] != q)
		new_line[(*l)++] = line[(*i)++];
	if (line[*i])
		new_line[(*l)++] = line[(*i)++];
	return (1);
}

int	handle_redirects(char *line, char *new_line, int *i, int *l)
{
	new_line[(*l)++] = ' ';
	while (line[*i] && (line[*i] == '<' || line[*i] == '>'))
		new_line[(*l)++] = line[(*i)++];
	new_line[(*l)++] = ' ';
	return (1);
}

int	len_forma(char *line, int i, int l)
{
	char	q;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				i++;
			if (line[i])
				i++;
		}
		else if (ft_strchr("<>", line[i]))
		{
			l += 2;
			while (line[i] && ft_strchr("<>", line[i]))
				i++;
		}
		else
			i++;
	}
	return (l + i + 1);
}

char	*fix_line(char *line)
{
	char	*new_line;
	int		i;
	int		l;

	i = 0;
	l = 0;
	new_line = ft_malloc(len_forma(line, 0, 0) * sizeof(char));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			handle_quotes(line, new_line, &i, &l);
		else if (line[i] == '<' || line[i] == '>')
			handle_redirects(line, new_line, &i, &l);
		else
			new_line[l++] = line[i++];
	}
	new_line[l] = '\0';
	return (new_line);
}
int	check_redirections(char **p_line)
{
	int	i;

	i = 0;
	if (p_line[0] && ft_strchr("<>", p_line[0][0]) && !p_line[1])
		return (0);
	while (p_line[i])
	{
		if (ft_strchr("<>", p_line[i][0]))
		{
			if (p_line[i + 1] && ft_strchr("<>", p_line[i + 1][0]))
				return (0);
			else if (p_line[i][1] && ft_strchr("<>", p_line[i][1]))
			{
				if (p_line[i][1] != p_line[i][0])
					return (0);
				else if (p_line[i][2])
					return (0);
			}
		}
		i++;
	}
	if (i > 0 && p_line[i - 1] && ft_strchr("<>", p_line[i - 1][0]))
		return (0);
	return (1);
}
