/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:35:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/28 15:05:51 by ppaulo-d         ###   ########.fr       */
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
	int output = open("monitoring.log", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (output < 0)
		return 0;
	while (temp)
	{
		cont = (t_data*)temp->content;
		pid = fork();
		if (pid == 0 && !ft_strncmp(cont->protocol, "PING", ft_strlen(cont->protocol)))
		{
			int pid2 = fork();
			if (pid2 == 0)
			{
				dup2(output, 1);
				close(output);
				ft_printf("=============================\n");
				ft_printf("NAME: %s\t Addres: %s\n", cont->name, cont->address);
				execlp("ping", "ping", cont->address, "-i", ft_itoa(cont->interval), NULL);
			}
			int pipes[2];
			pipe(pipes);
			int pid3 = fork();
			if (pid3 == 0)
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
				ft_printf("%s", line);
				line = get_next_line(pipes[0]);
			}
			//tratar(pipe[0]) < stdout
		}
	
		// else if (fork == 0 && HTML)
		// else if (fork == 0 && DNS)
		temp = temp->next;
	}
	int status;
	waitpid(pid, &status, 0);
	ft_printf("xxxxxxxxxxxxxxxx");
	// while (temp)
	// {
	// 	ft_printf("%s\n", ((t_data *)(temp->content))->address);
	// 	temp = temp->next;
	// }
//	ft_lstclear(&data, clean_data);
}