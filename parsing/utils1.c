/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:49:54 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/07 22:09:48 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_quotes(char *line, int i, int *dquote)
{
	if (line[i] == '\"')
	{
		*dquote = !(*dquote);
		i++;
	}
	else if (line[i] == '\'' && !(*dquote))
	{
		i++;
		while (line[i] && line[i] != '\'')
			i++;
		if (line[i])
			i++;
	}
	else
		i++;
	return (i);
}

int	handle_dollar(char **plus, char *line, char **info)
{
	int		i;
	char	*exp;

	i = 1;
	exp = expand_val(line, info);
	*plus = ft_strjoin1(*plus, exp);
	if (line[i] && (line[i] == '?' || ft_isdigit(line[i])))
		i++;
	else if (line[i] == '$')
	{
		while (line[i] == '$')
			i++;
		i--;
	}
	else
	{
		while (line[i] && ft_isalnum(line[i]))
			i++;
	}
	return (i);
}

char	*expand_val(char *s, char **info)
{
	char	*start;
	char	*temp;
	char	*dollar;

	(void)info;
	start = ft_strnstr(s, "$", ft_strlen(s));
	if (!start)
		return (NULL);
	if (!start[1])
		return (ft_strdup("$"));
	if (start[1] == '$')
		return (handle_dollar_case(start));
	temp = find_end(start);
	if (!temp)
		return (NULL);
	dollar = getenv(temp);
	if (dollar)
	{
		return (dollar);
	}
	if (start[1] && !ft_isalnum(start[1]))
		return (ft_strdup("$"));
	return (ft_strdup(""));
}

char	*ft_strjoin1(char const *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
		str[s1_len++] = s2[i++];
	str[s1_len] = '\0';
	return (str);
}

char	*handle_dollar_case(char *start)
{
	int	i;

	i = 0;
	while (start[i] && start[i] == '$')
		i++;
	return (ft_substr(start, 0, i - 1));
}
