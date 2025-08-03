/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:51:32 by w                 #+#    #+#             */
/*   Updated: 2025/08/02 11:57:29 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_word_len(const char *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != sep)
	{
		if (is_quote(s[i]))
			i = skip_quote(s, i);
		else
			i++;
	}
	return (i);
}

static int	count_words(const char *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (!s[i])
			break ;
		count++;
		i += get_word_len(&s[i], sep);
	}
	return (count);
}

static char	*copy_word(const char *s, int len)
{
	char	*word;
	char	quote;

	int (i), (j);
	i = 0;
	j = 0;
	word = (char *)ft_malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			word[j++] = quote;
			while (s[i] && s[i] != quote)
				word[j++] = s[i++];
			if (s[i] == quote)
				word[j++] = s[i++];
		}
		else
			word[j++] = s[i++];
	}
	word[j] = '\0';
	return (word);
}

static void	*free_all(char **arr, int count)
{
	while (--count >= 0)
		free(arr[count]);
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char sep)
{
	char	**res;

	int (i), (j), (len);
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s, sep) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (!s[i])
			break ;
		len = get_word_len(&s[i], sep);
		res[j] = copy_word(&s[i], len);
		if (!res[j])
			return (free_all(res, j));
		i += len;
		j++;
	}
	res[j] = NULL;
	return (res);
}