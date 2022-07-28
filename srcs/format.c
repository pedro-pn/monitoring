/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:15:50 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/28 17:35:07 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	format_out_ping(char *line, t_data content)
{
	char *time;
	time = ft_strnstr(line, "time", ft_strlen(line));
	if (time)
	{
		ft_printf("Name: %s\tProtocol: %s\t%s", content.name, content.protocol, time);
	}
}

void	format_out_http(char *line, t_data content)
{
	char	*code_line;
	char	**line_splt;
	int		code;
	code_line = ft_strnstr(line, "HTTP/", ft_strlen(line));
	if (code_line)
	{
		line_splt = ft_split(line, ' ');
		code = ft_atoi(line_splt[1]);
		ft_printf("Name: %s\t Protcol: %s\tcode_expected: %d\tgot: %d\n", content.name, content.protocol, content.http_code, code);
		clean_array((void **)line_splt);
	}
}