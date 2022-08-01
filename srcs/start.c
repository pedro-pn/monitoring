/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:46:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 15:33:17 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	monitoring_init(t_list **data, int argc, char *argv[], int *log_fd)
{
	check_args(argc, argv);
	*data = NULL;
	read_file(data);
	*log_fd = open(LGFILE, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (*log_fd < 0)
		error_handle(OUTFAIL);
	print_menu(*log_fd);
}

int	monitoring_start(t_list *data, int log_fd)
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
			status = start_ping(*cont, log_fd);
		else if (pid == 0 && !strcmp(cont->protocol, "HTTP"))
			status = start_http(*cont, log_fd);
		else if (pid == 0 && !strcmp(cont->protocol, "DNS"))
			status = start_dns(*cont, log_fd);
		if (pid == 0)
			return (status) ;
		data = data->next;
	}
	return (EXIT_SUCCESS);
}
