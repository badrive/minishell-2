/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:04:57 by ielyatim          #+#    #+#             */
/*   Updated: 2025/08/03 21:21:44 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../parsing/parsing.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	i = 0;
	while (i < len && s[start + i])
		i++;
	str = ft_malloc(i + 1);
	if (str)
	{
		i = 0;
		while (i < len && s[start])
			str[i++] = s[start++];
		str[i] = '\0';
	}
	return (str);
}
