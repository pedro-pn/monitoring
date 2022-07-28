/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:35:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/28 20:17:43 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"
#include <sys/wait.h>
#include <sys/types.h>

int	main(int argc, char *argv[])
{
	t_list	*data;
	t_list	*temp;
	t_data	*cont;
	int		pid;
	if (argc < 2)
		return 0;
	data = NULL;
	read_file(&data, argv[1]);
	temp = data;
	int output = open("monitoring.log", O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (output < 0)
		return 0;
	while (temp)
	{
		cont = (t_data*)temp->content;
		pid = fork();
		if (pid == 0 && !ft_strncmp(cont->protocol, "PING", ft_strlen(cont->protocol)))
		{
			int pipes[2];
			pipe(pipes);
			int pid2 = fork();
			if (pid2 == 0)
			{
				close(pipes[0]);
				dup2(pipes[1], 1);
				close(pipes[1]);
				execlp("ping", "ping", cont->address, "-i", ft_itoa(cont->interval), NULL);
			}
			close(pipes[1]);
			char *line;
			line = get_next_line(pipes[0]);
			while (line){
				write(output, line, ft_strlen(line));
				write(output, "\n", 1);
				format_out_ping(line, *cont, output);
				free(line);
				line = get_next_line(pipes[0]);
			}

		}

		else if (pid == 0 && !ft_strncmp(cont->protocol, "HTTP", ft_strlen(cont->protocol)))
		{
			int index = 1;
			int pid2;
			int pid3;
			int pipes[2];
			char *line;
			char	*line_out;
			
			while (index)
			{
				if (index > 1)
					sleep(cont->interval);
				pipe(pipes);
				pid2 = fork();
				if (pid2 == 0)
				{
					close(pipes[0]);
					dup2(pipes[1], 1);
					close(pipes[1]);
					execlp("curl", "curl", "-s", "-i", cont->address, NULL);
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
				format_out_http(line_out, *cont, output);
				free(line_out);
				write(output, "\n", 1);
				free(line);
				index++;
			}
		}
		else if (pid == 0 && !ft_strncmp(cont->protocol, "DNS", ft_strlen(cont->protocol)))
		{
			int pipes[2];
			char	*line;
			int pid2;
			int index;
			char	*line_out;
			index = 1;
			while (index){
				if (index > 1)
					sleep(cont->interval);
				pipe(pipes);
				pid2 = fork();
				if (pid2 == 0)
				{
					close(pipes[0]);
					dup2(pipes[1], 1);
					close(pipes[1]);
					//ft_printf("dns: %s\nAddress:%\n")
					execlp("dig", "dig", ft_strjoin("@", cont->dns_server), cont->address, NULL);
				}
				close(pipes[1]);
				line = get_next_line(pipes[0]);
				while (line)
				{
					write(output, line, ft_strlen(line));
					if (ft_strnstr(line, cont->address, ft_strlen(cont->address)))
						line_out = ft_strdup(line);
					free(line);
					line = get_next_line(pipes[0]);
				}
				format_out_dns(line_out, *cont, output);
				free(line_out);
				close(pipes[0]);
				free(line);
				index++;
			}
		}
		temp = temp->next;
	}
	int status;
	int processes;
	processes = ft_lstsize(data);
	for (int i = 0; i < processes; i++)
		wait(NULL);
	ft_printf("xxxxxxxxxxxxxxxx");
	// while (temp)
	// {
	// 	ft_printf("%s\n", ((t_data *)(temp->content))->address);
	// 	temp = temp->next;
	// }
//	ft_lstclear(&data, clean_data);
}