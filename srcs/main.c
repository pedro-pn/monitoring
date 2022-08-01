/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:35:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 15:33:05 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	main(int argc, char *argv[])
{
	t_list	*data;
	int		processes;
	int		log_fd;
	int		status;

	monitoring_init(&data, argc, argv, &log_fd);
	status = monitoring_start(data, log_fd);
	processes = ft_lstsize(data);
	for (int i = 0; i < processes; i++)
		wait(NULL);
	ft_lstclear(&data, clean_data);
	close(log_fd);
	if (status)
		error_handle(status);
	return (0);
}
