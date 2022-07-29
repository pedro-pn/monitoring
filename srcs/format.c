/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:15:50 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 13:05:00 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	format_out_ping(char *line, t_data content, int output)
{
	char *time;
	time = ft_strnstr(line, "time", ft_strlen(line));
	if (time)
	{
		ft_printf("# Name: %s\tProtocol: %s\t%s",
		content.name, content.protocol, time);
		dprintf(output, "# Name: %s\tProtocol: %s\t%s",
		content.name, content.protocol, time);
	}
}

void	format_out_http(char *line, t_data content, int output)
{
	char	**line_splt;
	int		code;

	line_splt = ft_split(line, ' ');
	code = ft_atoi(line_splt[1]);
	ft_printf("# Name: %s\t Protcol: %s\t Request: %s\t code_expected: %d\tgot: %d\n",
	content.name, content.protocol, content.http_method, content.http_code, code);
	dprintf(output, "# Name: %s\t Protcol: %s\t Request: %s\t code_expected: %d\tgot: %d\n",
	content.name, content.protocol, content.http_method, content.http_code, code);
	clean_array((void **)line_splt);
}

void	format_out_dns(char *line, t_data content, int output)
{
	ft_printf("# Name: %s\tProtocol: %s\tAddress: %s\tDNS_server: %s\n# Got: %s\n",
	content.name, content.protocol, content.address, content.dns_server, line);
	dprintf(output, "# Name: %s\tProtocol: %s\tAddress: %s\tDNS_server: %s\n# Got: %s\n",
	content.name, content.protocol, content.address, content.dns_server, line);
}
