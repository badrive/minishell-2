/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:09:02 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/07 22:09:26 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_pipe_syntax_error(char *line, int i)
{
	if (line[i] && line[i] == '|')
		return (-1);
	while (line[i] && line[i] == ' ')
	{
		i++;
		if (line[i] && line[i] == '|')
			return (-1);
	}
	return (i);
}

int	check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			while (line[i] == ' ' || line[i] == '<')
				i++;
			if (line[i] == '$')
				return (0);
		}
		i++;
	}
	return (1);
}

char	**expand_and_split(char *line, char **info)
{
	char	*expanded;
	char	**split_line;

	if (check(line) == 1)
	{
		expanded = expand_line(line, 0, ft_strdup(""), info);
		if (!expanded)
			return (NULL);
	}
	else
		expanded = ft_strdup(line);
	split_line = ft_split(expanded, '|');
	return (split_line);
}

char	*expand_line(char *line, int dquote, char *plus, char **info)
{
	int		i;
	char	*line_plus;
	char	*temp_plus;

	while (line && *line)
	{
		i = 0;
		while (line[i] && line[i] != '$')
			i = skip_quotes(line, i, &dquote);
		line_plus = ft_substr(line, 0, i);
		temp_plus = ft_strjoin1(plus, line_plus);
		plus = temp_plus;
		if (line[i] == '$')
		{
			line += i;
			i = handle_dollar(&plus, line, info);
		}
		line += i;
	}
	return (plus);
}

char	*expand_line1(char *line, char *plus, char **info)
{
	int		i;
	char	*line_plus;
	char	*temp_plus;

	while (line && *line)
	{
		i = 0;
		while (line[i] && line[i] != '$')
			i++;
		line_plus = ft_substr(line, 0, i);
		temp_plus = ft_strjoin(plus, line_plus);
		plus = temp_plus;
		if (line[i] == '$')
		{
			line += i;
			i = handle_dollar(&plus, line, info);
		}
		line += i;
	}
	return (plus);
}
