/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocols.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:10:33 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/28 21:59:37 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	start_ping(t_data data, int output)
{
	int pipes[2];
	char *line;
	pipe(pipes);
	int pid2 = fork();
	if (pid2 == 0)
	{
		close(pipes[0]);
		dup2(pipes[1], 1);
		close(pipes[1]);
		execlp("ping", "ping", data.address, "-i", ft_itoa(data.interval), NULL);
	}
	close(pipes[1]);
	line = get_next_line(pipes[0]);
	while (line){
		write(output, line, ft_strlen(line));
		write(output, "\n", 1);
		format_out_ping(line, data, output);
		free(line);
		line = get_next_line(pipes[0]);
	}
}

void	start_http(t_data data, int output)
{
	int 	index = 1;
	int		pid;
	int		pipes[2];
	char 	*line;
	char	*line_out;
	
	while (index)
	{
		if (index > 1)
			sleep(data.interval);
		pipe(pipes);
		pid = fork();
		if (pid == 0)
		{
			close(pipes[0]);
			dup2(pipes[1], 1);
			close(pipes[1]);
			execlp("curl", "curl", "-s", "-i", data.address, NULL);
		}
		close(pipes[1]);
		line = get_next_line(pipes[0]);
		while (line)
		{
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
		index++;
	}
}

void	start_dns(t_data data, int output)
{
	int		pipes[2];
	char	*line;
	int		pid2;
	int		index;
	char	*line_out;
	
	index = 1;
	while (index){
		if (index > 1)
			sleep(data.interval);
		pipe(pipes);
		pid2 = fork();
		if (pid2 == 0)
		{
			close(pipes[0]);
			dup2(pipes[1], 1);
			close(pipes[1]);
			execlp("dig", "dig", ft_strjoin("@", data.dns_server), data.address, NULL);
		}
		close(pipes[1]);
		line = get_next_line(pipes[0]);
		while (line)
		{
			write(output, line, ft_strlen(line));
			if (ft_strnstr(line, data.address, ft_strlen(line)))
				line_out = ft_strdup(line);
			free(line);
			line = get_next_line(pipes[0]);
		}
		format_out_dns(line_out, data, output);
		free(line_out);
		close(pipes[0]);
		index++;
	}
}