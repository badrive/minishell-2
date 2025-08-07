/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:09:51 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/07 22:25:46 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*find_end(char *start)
{
	int	i;

	i = 1;
	if (start[i] && start[i] == '?')
		return (ft_substr(start + 1, 0, i));
	if (start[i] && ft_isdigit(start[i]))
		return (ft_substr(start + 1, 0, i));
	while (start[i] && ft_isalnum(start[i]))
		i++;
	return (ft_substr(start + 1, 0, i - 1));
}
