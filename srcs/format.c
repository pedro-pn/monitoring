/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:15:50 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 10:31:06 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	format_out_ping(char *line, t_data content, int output)
{
	char	*time;
	char	*packets;
	time = ft_strnstr(line, "time", ft_strlen(line));
	packets = ft_strnstr(line, "packets", ft_strlen(line));
	if (packets)
	{
		ft_printf("# %s\n", packets);
		dprintf(output, "# %s", packets);
	}
	else if (time)
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
	ft_printf("# Name: %s\t Protocol: %s\t Request: %s\t code_expected: %d\tgot: %d\n\n",
	content.name, content.protocol, content.http_method, content.http_code, code);
	dprintf(output, "# Name: %s\t Protocol: %s\t Request: %s\t code_expected: %d\tgot: %d\n",
	content.name, content.protocol, content.http_method, content.http_code, code);
	clean_array((void **)line_splt);
}

void	format_out_dns(char *line, t_data content, int output)
{
	if (line){
		ft_printf("# Name: %s\tProtocol: %s\tAddress: %s\tDNS_server: %s\n# Got: %s\n",
		content.name, content.protocol, content.address, content.dns_server, line);
		dprintf(output, "# Name: %s\tProtocol: %s\tAddress: %s\tDNS_server: %s\n# Got: %s\n",
		content.name, content.protocol, content.address, content.dns_server, line);
	}
}

void	print_menu(int output)
{
	int		input;
	char	*line;
	
	input = open("monitoring.db", O_RDONLY);
	if (input < 0)
		return ;
	dprintf(output, "===================================monitoring===================================\n");
	line = get_next_line(input);
	while (line){
		write(output, line, ft_strlen(line));
		free(line);
		line = get_next_line(input);
	}
	dprintf(output, "\n=====================================config=====================================\n\n");
	close(input);
}

int	write_ping(t_data data, int pipe, int fd_log)
{
	char	*line;
	
	line = get_next_line(pipe);
	if (!line)
		return (1);
	while (line){
		write(fd_log, line, ft_strlen(line));
		write(fd_log, "\n", 1);
		format_out_ping(line, data, fd_log);
		free(line);
		line = get_next_line(pipe);
	}
	return (0);
}

int	write_http(t_data data, int pipe, int fd_log)
{
	char	*line;
	char	*line_out;
	
	line = get_next_line(pipe);
	line_out = NULL;
	if (!line)
		return (-1);
	while (line){
		write(fd_log, line, ft_strlen(line));
		if (ft_strnstr(line, "HTTP/", ft_strlen(line)))
			line_out = ft_strdup(line);
		free(line);
		line = get_next_line(pipe);
	}
	format_out_http(line_out, data, fd_log);
	if (line_out)
		free(line_out);
	write(fd_log, "\n", 1);
	return (0);
}

int	write_dns(t_data data, int pipe, int fd_log)
{
	char	*line;
	char	*line_out;

	line_out = NULL;
	line = get_next_line(pipe);
	while (line){
		write(fd_log, line, ft_strlen(line));
		if (ft_strnstr(line, data.address, ft_strlen(line)) && line[0] != ';')
			line_out = ft_strdup(line);
		free(line);
		line = get_next_line(pipe);
	}
	format_out_dns(line_out, data, fd_log);
	if (line_out)
		free(line_out);
	return (0);
}
