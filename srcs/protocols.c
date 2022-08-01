/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocols.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:10:33 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 13:58:10 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	start_ping(t_data data, int log_fd)
{
	int		pipes[2];
	int		pid;

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
		if (write_ping(data, pipes[0], log_fd))
			return (1);
		close(pipes[0]);
		sleep(data.interval);
	}
	return (EXIT_SUCCESS);
}

int	start_http(t_data data, int log_fd)
{
	int		pid;
	int		pipes[2];
	
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
			execlp("curl", "curl", data.address, "-siX", data.http_method, NULL);
		}
		close(pipes[1]);
		if (write_http(data, pipes[0], log_fd))
			return (-1);
		close(pipes[0]);
		sleep(data.interval);
	}
	return (EXIT_SUCCESS);
}

int	start_dns(t_data data, int log_fd)
{
	int		pipes[2];
	int		pid;
	
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
		if (write_dns(data, pipes[0], log_fd))
			return (-1);
		close(pipes[0]);
		sleep(data.interval);
	}
	return (EXIT_SUCCESS);
}
