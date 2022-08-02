/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:15:50 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/02 11:16:07 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	format_out_ping(char *line, t_data content, int log_fd)
{
	char	*time_ms;
	char	*packets;
	char	*time_s;
	time_t	time_now;
	
	time_now = time(NULL);
	time_s = ctime(&time_now);
	ft_memrpl(time_s, '\n', 0, ft_strlen(time_s));
	time_ms = ft_strnstr(line, "time", ft_strlen(line));
	packets = ft_strnstr(line, "packets", ft_strlen(line));
	if (packets)
	{
		ft_printf("# %s\n", packets);
		dprintf(log_fd, "# %s", packets);
	}
	else if (time_ms)
	{
		ft_printf("# [%s]\n# Name: %s | Protocol: %s | Address: %s | %s",
		time_s, content.name, content.protocol, content.address, time_ms);
		dprintf(log_fd, "# [%s]\n# Name: %s | Protocol: %s | Address: %s | %s",
		time_s, content.name, content.protocol, content.address, time_ms);
	}
}

void	format_out_http(char *line, t_data content, int log_fd)
{
	char	**line_splt;
	char	*status;
	char	*color;
	char	*time_s;
	int		code;
	time_t	time_now;

	time_now = time(NULL);
	time_s = ctime(&time_now);
	ft_memrpl(time_s, '\n', 0, ft_strlen(time_s));
	line_splt = ft_split(line, ' ');
	code = ft_atoi(line_splt[1]);
	if (code ==  content.http_code){
		status = HEALTHY;
		color = GREEN;
	}
	else{
		status = UNHEALTHY;
		color = RED;
	}
	ft_printf("# [%s]\n# Name: %s | Protocol: %s | Address: %s | Request: %s | code_expected: %d got: %d\n# Status: %s%s%s\n\n",
	time_s, content.name, content.protocol, content.address, content.http_method, content.http_code, code, color, status, NC);
	dprintf(log_fd, "# [%s]\n# Name: %s | Protocol: %s | Address: %s | Request: %s | code_expected: %d got: %d\n# Status: %s\n\n",
	time_s, content.name, content.protocol, content.address, content.http_method, content.http_code, code, status);
	clean_array((void **)line_splt);
}

void	format_out_dns(char *line, t_data content, int log_fd)
{
	time_t	time_now;
	char	*time_s;

	time_now = time(NULL);
	time_s = ctime(&time_now);
	ft_memrpl(time_s, '\n', 0, ft_strlen(time_s));
	if (line){
		ft_printf("# [%s]\n# Name: %s | Protocol: %s | Address: %s | DNS_server: %s\n# Got: %s# Status: %s%s%s\n\n",
		time_s, content.name, content.protocol, content.address, content.dns_server, line, GREEN, HEALTHY, NC);
		dprintf(log_fd, "# [%s]\n# Name: %s | Protocol: %s | Address: %s | DNS_server: %s\n# Got: %s# Status: %s\n\n",
		time_s, content.name, content.protocol, content.address, content.dns_server, line, HEALTHY);
	}
	else{
		ft_printf("# [%s]\n# Name: %s | Protocol: %s | Address: %s | DNS_server: %s\n# Status: %s%s%s\n\n",
		time_s, content.name, content.protocol, content.address, content.dns_server, RED, UNHEALTHY, NC);
		dprintf(log_fd, "# [%s]\n# Name: %s | Protocol: %s | Address: %s | DNS_server: %s\n# Status: %s\n\n",
		time_s, content.name, content.protocol, content.address, content.dns_server, UNHEALTHY);
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
	write(log_fd, "\n", 1);
	while (line){
		write(log_fd, line, ft_strlen(line));
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
	write(log_fd, "\n", 1);
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
