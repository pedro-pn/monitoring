/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:15:50 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 22:38:27 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	format_out_ping(char *line, t_data content, int log_fd)
{
	char	*time_ms;
	char	*packets;
	char	*status;
	time_t	time_now;
	
	time_now = time(NULL);
	time_ms = ft_strnstr(line, "time", ft_strlen(line));
	if (time_ms)
		ft_memrpl(time_ms, '\n', 0, ft_strlen(time_ms));
	packets = ft_strnstr(line, "packets", ft_strlen(line));
	if (packets)
	{
		ft_printf("# %s\n", packets);
		dprintf(log_fd, "# %s", packets);
	}
	else if (time_ms)
	{
		ft_printf("# Name: %s | Protocol: %s | Address: %s | %s | %s",
		content.name, content.protocol, content.address, time_ms, ctime(&time_now));
		dprintf(log_fd, "# Name: %s | Protocol: %s | Address: %s | %s | %s",
		content.name, content.protocol, content.address, time_ms, ctime(&time_now));
	}
}

void	format_out_http(char *line, t_data content, int log_fd)
{
	char	**line_splt;
	char	*status;
	int		code;
	time_t	time_now;

	time_now = time(NULL);
	line_splt = ft_split(line, ' ');
	code = ft_atoi(line_splt[1]);
	if (code ==  content.http_code)
		status = HEALTHY;
	else
		status = BAD;
	ft_printf("# Name: %s | Protocol: %s | Address: %s | Request: %s | code_expected: %d got: %d | Status: %s | %s\n",
	content.name, content.protocol, content.address, content.http_method, content.http_code, code, status, ctime(&time_now));
	dprintf(log_fd, "# Name: %s | Protocol: %s | Address: %s | Request: %s | code_expected: %d got: %d | Status: %s | %s\n",
	content.name, content.protocol, content.address, content.http_method, content.http_code, code, status, ctime(&time_now));
	clean_array((void **)line_splt);
}

void	format_out_dns(char *line, t_data content, int log_fd)
{
	time_t	time_now;

	time_now = time(NULL);
	if (line){
		ft_printf("# Name: %s | Protocol: %s | Address: %s | DNS_server: %s | %s# Got: %s\n",
		content.name, content.protocol, content.address, content.dns_server, ctime(&time_now), line);
		dprintf(log_fd, "# Name: %s | Protocol: %s | Address: %s | DNS_server: %s | %s# Got: %s\n",
		content.name, content.protocol, content.address, content.dns_server, ctime(&time_now), line);
	}
}

void	print_menu(int log_fd)
{
	int		input;
	char	*line;
	
	input = open("monitoring.db", O_RDONLY);
	if (input < 0)
		return ;
	dprintf(log_fd, "===================================monitoring===================================\n");
	line = get_next_line(input);
	while (line){
		write(log_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(input);
	}
	dprintf(log_fd, "\n=====================================config=====================================\n\n");
	close(input);
}

int	write_ping(t_data data, int pipe, int log_fd)
{
	char	*line;
	
	line = get_next_line(pipe);
	if (!line)
		return (1);
	while (line){
		write(log_fd, line, ft_strlen(line));
		write(log_fd, "\n", 1);
		format_out_ping(line, data, log_fd);
		free(line);
		line = get_next_line(pipe);
	}
	return (0);
}

int	write_http(t_data data, int pipe, int log_fd)
{
	char	*line;
	char	*line_out;
	
	line = get_next_line(pipe);
	line_out = NULL;
	if (!line)
		return (-1);
	while (line){
		write(log_fd, line, ft_strlen(line));
		if (ft_strnstr(line, "HTTP/", ft_strlen(line)))
			line_out = ft_strdup(line);
		free(line);
		line = get_next_line(pipe);
	}
	format_out_http(line_out, data, log_fd);
	if (line_out)
		free(line_out);
	write(log_fd, "\n", 1);
	return (0);
}

int	write_dns(t_data data, int pipe, int log_fd)
{
	char	*line;
	char	*line_out;

	line_out = NULL;
	line = get_next_line(pipe);
	while (line){
		write(log_fd, line, ft_strlen(line));
		if (ft_strnstr(line, data.address, ft_strlen(line)) && line[0] != ';')
			line_out = ft_strdup(line);
		free(line);
		line = get_next_line(pipe);
	}
	format_out_dns(line_out, data, log_fd);
	if (line_out)
		free(line_out);
	return (0);
}
