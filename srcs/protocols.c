/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocols.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:10:33 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/31 23:43:35 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	start_ping(t_data data, int output)
{
	int		pipes[2];
	int		pid;
	char	*line;

	while (1){
		if (pipe(pipes) == -1)
			return (EPIPE);
		pid = fork();
		if (pid == -1)
			return (EFORK);
		else if (pid == 0){
			close(pipes[0]);
			dup2(pipes[1], 1);
			close(pipes[1]);
			execlp("ping", "ping", data.address, "-c", "1", NULL);
		}
		close(pipes[1]);
		line = get_next_line(pipes[0]);
		if (!line)
			return (EXIT_FAILURE);
		while (line){
			write(output, line, ft_strlen(line));
			write(output, "\n", 1);
			format_out_ping(line, data, output);
			free(line);
			line = get_next_line(pipes[0]);
		}
		sleep(data.interval);
	}
	return (EXIT_SUCCESS);
}

int	start_http(t_data data, int output)
{
	int		pid;
	int		pipes[2];
	char	*line;
	char	*line_out;
	
	while (1)
	{
		if (pipe(pipes) == -1)
			return (EPIPE);
		pid = fork();
		if (pid == -1)
			return (EFORK);
		else if (pid == 0){
			close(pipes[0]);
			dup2(pipes[1], 1);
			close(pipes[1]);
			execlp("curl", "curl", "-s", "-i", data.address, "-X", data.http_method, NULL);
		}
		close(pipes[1]);
		line = get_next_line(pipes[0]);
		if (!line)
			return (-1);
		while (line){
			write(output, line, ft_strlen(line));
			if (ft_strnstr(line, "HTTP/", ft_strlen(line)))
				line_out = ft_strdup(line);
			free(line);
			line = get_next_line(pipes[0]);
		}
		close(pipes[0]);
		format_out_http(line_out, data, output);
		free(line_out);
		write(output, "\n", 1);
		sleep(data.interval);
	}
	return (EXIT_SUCCESS);
}

int	start_dns(t_data data, int output)
{
	int		pipes[2];
	char	*line;
	int		pid;
	char	*line_out = NULL;
	
	while (1){
		if (pipe(pipes) == -1)
			return (EPIPE);
		pid = fork();
		if (pid == -1)
			return (EFORK);
		else if (pid == 0){
			close(pipes[0]);
			dup2(pipes[1], 1);
			close(pipes[1]);
			execlp("dig", "dig", ft_strjoin("@", data.dns_server), data.address, NULL);
		}
		close(pipes[1]);
		line = get_next_line(pipes[0]);
		while (line){
			write(output, line, ft_strlen(line));
			if (ft_strnstr(line, data.address, ft_strlen(line)) && line[0] != ';')
				line_out = ft_strdup(line);
			free(line);
			line = get_next_line(pipes[0]);
		}
		format_out_dns(line_out, data, output);
		if (line_out)
			free(line_out);
		close(pipes[0]);
		sleep(data.interval);
	}
	return (EXIT_SUCCESS);
}
