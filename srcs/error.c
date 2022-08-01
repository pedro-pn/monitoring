/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:58:45 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 13:28:10 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

static int	check_interval(char	*interval);

void	error_handle(int code, char *name)
{
	if (code == FILEOP)
		fprintf(stderr, "Couldn't open 'monitoring.db'.\n");
	else if (code == INVINPUT)
		fprintf(stderr, "Invalid format in 'monitoring.db' file.\n");
	else if (code == OUTFAIL)
		fprintf(stderr, "Couldn't create or modify 'monitoring.log'.\n");
	else if (code == INVARG)
		fprintf(stderr, "Try '--simplify' to visualize log.\n");
	else if (code == MANYARGS)
		fprintf(stderr, "monitoring allows only '--simplify' option.\n");
	else if (code == EFORK)
		fprintf(stderr, "monitoring: failed to fork.\n");
	else if (code == EPIPE)
		fprintf(stderr, "monitorig: failed to open pipe.\n");
	else if (code == INVPROTO){
		fprintf(stderr, "'%s' protocol invalid.\n", name);
		return ;
	}
	else if (code == EINTERVAL){
		fprintf(stderr, "Interval '%s' invalid.\n", 
			(char *)ft_memrpl(name, '\n', 0, ft_strlen(name)));
		return ;
	}
	exit(EXIT_FAILURE);
}

void	check_file_format(char **line, t_list **data, char *interval, int method)
{
	int num_col;

	num_col = 0;
	while (line[num_col])
		num_col++;
	if (num_col != method){
		clean_array((void **)line);
		ft_lstclear(data, clean_data);
		error_handle(INVINPUT, NULL);
	}
	if (check_interval(interval) == 0){
		error_handle(EINTERVAL, interval);
		clean_array((void **)line);
		ft_lstclear(data, clean_data);
		exit(EXIT_FAILURE);
	}
}

static int	check_interval(char	*interval)
{
	char	*trim_inter;
	int		index;

	trim_inter = ft_strtrim(interval, "\n\t");
	index = 0;
	while(trim_inter[index])
	{
		if (!ft_isdigit(trim_inter[index])){
			free(trim_inter);
			return (0);
		}
		index++;
	}
	free(trim_inter);
	return (1);
}