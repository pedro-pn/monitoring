/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d < ppaulo-d@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:11:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/04/19 22:44:01 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_start(const char *s1, const char *set)
{
	int	flag;
	int	s1_index;
	int	set_index;

	flag = 0;
	s1_index = 0;
	while (s1[s1_index])
	{
		flag = 0;
		set_index = 0;
		while (set[set_index])
		{
			if (s1[s1_index] == set[set_index])
				flag++;
			set_index++;
		}
		if (flag == 0)
			break ;
		s1_index++;
	}
	return (s1_index);
}

static int	get_end(const char *s1, const char *set)
{
	int	flag;
	int	s1_index;
	int	set_index;

	flag = 0;
	s1_index = (int) ft_strlen(s1) - 1;
	while (s1_index >= 0)
	{
		flag = 0;
		set_index = 0;
		while (set[set_index])
		{
			if (s1[s1_index] == set[set_index])
				flag++;
			set_index++;
		}
		if (flag == 0)
			break ;
		s1_index--;
	}
	return (s1_index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set) - start + 1;
	str = ft_substr(s1, start, end);
	return (str);
}
