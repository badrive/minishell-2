/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:49:54 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/05 18:27:01 by bfaras           ###   ########.fr       */
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

int check(char *line)
{
	int i =0;
	while(line[i])
		{
		if(line[i] == '<' && line[i+1] == '<')
			{
				while(line[i] == ' ' || line[i] == '<' )
					i++;
				if(line[i] == '$')
					return 0;
			}
			i++;
		}
		return 1;
}

char	**expand_and_split(char *line, char **info)
{
	char	*expanded;
	char	**split_line;

	if(check(line) == 1)
	{
		expanded = expand_line(line, 0, ft_strdup(""), info);
		if (!expanded)
			return (NULL);
	}
	else 
		expanded = ft_strdup(line);
	split_line = ft_split(expanded, '|');
	// free(expanded);
	return (split_line);
}
// expend

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
		// free(line_plus);
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
		// free(line_plus);
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
	// free(exp);
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
	// dollar = get_env_value(temp, info->my_envp);
	dollar = getenv(temp);
	// free(temp);
	if (dollar)
	{
		return (dollar);
	}
	// if (start[1] && start[1] == '?')
	// 	return (ft_itoa(g_es));
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

char	*find_end(char *start)
{
	int i;

	i = 1;
	if (start[i] && start[i] == '?')
		return (ft_substr(start + 1, 0, i));
	if (start[i] && ft_isdigit(start[i]))
		return (ft_substr(start + 1, 0, i));
	while (start[i] && ft_isalnum(start[i]))
		i++;
	return (ft_substr(start + 1, 0, i - 1));
}
