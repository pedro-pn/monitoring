/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:22:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 13:32:40 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrpl(char *s, int old, int new, size_t n)
{
	int	index;

	index = 0;
	if ((unsigned char) old == (unsigned char) new)
		return (s);
	while (index < (int) n)
	{
		if (s[index] == (unsigned char) old)
			s[index] = (unsigned char) new;
		index++;
	}
	return (s);
}
