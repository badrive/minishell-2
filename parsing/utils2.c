/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:02:15 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/05 14:13:53 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_split(char *line, int i, char q)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i];
			i++;
			while (line[i] && line[i] != q)
				i++;
			i++;
		}
		if (line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				return (2);
			return (1);
		}
		if (line[i] == '<')
		{
			if (line[i + 1] && line[i + 1] == '<')
				return (4);
			return (3);
		}
		i++;
	}
	return (0);
}

int	d_quote(char *line, int dquote, int quote, int i)
{
	char	q;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			if (q == '\"')
				dquote++;
			else
				quote++;
			while (line[i] && line[i] != q)
				i++;
			if (line[i] == '\0')
				break ;
			if (line[i] == '\"')
				dquote++;
			if (line[i] == '\'')
				quote++;
		}
		i++;
	}
	if (dquote % 2 != 0 || quote % 2 != 0)
		return (0);
	return (1);
}

int	check_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && line[i] == '|')
		return (0);
	i = if_check_pipe(line, i, '\0');
	if (i == -1)
		return (0);
	i--;
	while (i >= 0 && line[i] == ' ')
		i--;
	if (i >= 0 && line[i] == '|')
		return (0);
	return (1);
}

int	if_check_pipe(char *line, int i, char q)
{
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
		else if (line[i] == '|')
		{
			i++;
			i = is_pipe_syntax_error(line, i);
			if (i == -1)
				return (-1);
		}
		else
			i++;
	}
	return (i);
}

char	*qoute_remov(char *line, char q, int i, int l)
{
	char *new_line;

	new_line = ft_malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				new_line[l++] = line[i++];
			if (line[i])
				i++;
		}
		else
			new_line[l++] = line[i++];
	}
	new_line[l] = '\0';
	return (new_line);
}