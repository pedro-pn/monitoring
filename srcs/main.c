/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:35:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 20:14:13 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	main(int argc, char *argv[])
{
	t_list	*data;
	int		processes;
	int		output_fd;

	monitoring_init(&data, argc, argv, &output_fd);
	monitoring_start(data, output_fd);
	processes = ft_lstsize(data);
	for (int i = 0; i < processes; i++)
		wait(NULL);
	ft_printf("xxxxxxxxxxxxxxxx\n"); // test purpose
	ft_lstclear(&data, clean_data);
	close(output_fd);
	return (0);
}
