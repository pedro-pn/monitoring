/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:35:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 14:54:27 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	main(int argc, char *argv[])
{
	t_list	*data;
	t_list	*temp;
	t_data	*cont;
	int		pid;
	int		processes;
	int		output;
	
	check_args(argc, argv);
	data = NULL;
	read_file(&data, "monitoring.db");
	temp = data;
	output = open("monitoring.log", O_WRONLY | O_APPEND | O_CREAT, 0664);
	print_menu(output);
	if (output < 0)
		error_handle(OUTFAIL);
	while (temp){
		cont = (t_data*)temp->content;
		pid = fork();
		if (pid == 0 && !ft_strncmp(cont->protocol, "PING", ft_strlen(cont->protocol)))
			start_ping(*cont, output);
		else if (pid == 0 && !ft_strncmp(cont->protocol, "HTTP", ft_strlen(cont->protocol)))
			start_http(*cont, output);
		else if (pid == 0 && !ft_strncmp(cont->protocol, "DNS", ft_strlen(cont->protocol)))
			start_dns(*cont, output);
		if (pid == 0) // make sure child process don't loop
			break ;
		temp = temp->next;
	}
	processes = ft_lstsize(data);
	for (int i = 0; i < processes; i++)
		wait(NULL);
	ft_printf("xxxxxxxxxxxxxxxx\n"); // test purpose
	ft_lstclear(&data, clean_data);
	close(output);
	if (pid == 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
