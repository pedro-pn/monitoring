/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:35:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/27 22:31:45 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	main(int argc, char *argv[])
{
	t_list	*data;
	t_list	*temp;

	if (argc < 2)
		return 0;
	data = NULL;
	read_file(&data, argv[1]);
	temp = data;
	while (temp)
	{
		ft_printf("%s\n", ((t_data *)(temp->content))->address);
		temp = temp->next;
	}
	ft_lstclear(&data, clean_data);
}