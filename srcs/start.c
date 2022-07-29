/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:46:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 20:12:03 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	monitoring_init(t_list **data, int argc, char *argv[], int *output_fd)
{
	check_args(argc, argv);
	*data = NULL;
	read_file(data, "monitoring.db");
	*output_fd = open("monitoring.log", O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (*output_fd < 0)
		error_handle(OUTFAIL, NULL);
	print_menu(*output_fd);
}

void	monitoring_start(t_list *data, int output_fd)
{
	t_data	*cont;
	int		pid;

	while (data){
		cont = (t_data *)data->content;
		pid = fork();
		if (pid == 0 && !ft_strncmp(cont->protocol, "PING", ft_strlen(cont->protocol)))
			start_ping(*cont, output_fd);
		else if (pid == 0 && !ft_strncmp(cont->protocol, "HTTP", ft_strlen(cont->protocol)))
			start_http(*cont, output_fd);
		else if (pid == 0 && !ft_strncmp(cont->protocol, "DNS", ft_strlen(cont->protocol)))
			start_dns(*cont, output_fd);
		if (pid == 0) // make sure child process don't loop
			break ;
		data = data->next;
	}
}