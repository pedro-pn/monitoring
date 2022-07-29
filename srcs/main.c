/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:35:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 00:03:18 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	main(int argc, char *argv[])
{
	t_list	*data;
	t_list	*temp;
	t_data	*cont;
	int		pid;
	int 	processes;
	
	if (argc < 2)
		error_handle(NARG);
	data = NULL;
	read_file(&data, argv[1]);
	temp = data;
	int output = open("monitoring.log", O_WRONLY | O_APPEND | O_CREAT, 0664);
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
		temp = temp->next;
	}
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
