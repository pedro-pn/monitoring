/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:07:45 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 13:23:37 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrpl(const char *str, int old, int new)
{
	int		index;
	int		str_len;
	char	*new_str;

	index = 0;
	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	new_str = malloc(sizeof(*new_str) * (str_len + 1));
	if (!new_str)
		return (NULL);
	new_str[str_len] = 0;
	while (str[index])
	{
		if (str[index] == (unsigned char) old)
			new_str[index] = (unsigned char) new;
		else
			new_str[index] = str[index];
		index++;
	}
	return (new_str);
}
