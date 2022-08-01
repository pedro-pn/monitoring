/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:46:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 12:56:02 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	monitoring_init(t_list **data, int argc, char *argv[], int *output_fd)
{
	check_args(argc, argv);
	*data = NULL;
	read_file(data);
	*output_fd = open(LGFILE, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (*output_fd < 0)
		error_handle(OUTFAIL, NULL);
	print_menu(*output_fd);
}

int	monitoring_start(t_list *data, int output_fd)
{
	t_data	*cont;
	int		pid;
	int		status;

	while (data){
		cont = (t_data *)data->content;
		pid = fork();
		if (pid < 0)
			return (EFORK);
		if (pid == 0 && !strcmp(cont->protocol, "PING"))
			status = start_ping(*cont, output_fd);
		else if (pid == 0 && !strcmp(cont->protocol, "HTTP"))
			status = start_http(*cont, output_fd);
		else if (pid == 0 && !strcmp(cont->protocol, "DNS"))
			status = start_dns(*cont, output_fd);
		if (pid == 0)
			return (status) ;
		data = data->next;
	}
	return (EXIT_SUCCESS);
}
