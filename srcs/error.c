/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:58:45 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 15:36:50 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

static int	check_interval(char	*interval);

void	error_handle(int code)
{
	if (code == FILEOP)
		fprintf(stderr, "Error: couldn't open 'monitoring.db'.\n");
	else if (code == INVINPUT)
		fprintf(stderr, "Error: invalid format in 'monitoring.db' file.\n");
	else if (code == OUTFAIL)
		fprintf(stderr, "Error: couldn't create or modify 'monitoring.log'.\n");
	else if (code == INVARG)
		fprintf(stderr, "Try '--simplify' to visualize log.\n");
	else if (code == MANYARGS)
		fprintf(stderr, "monitoring allows only '--simplify' option.\n");
	else if (code == EFORK)
		fprintf(stderr, "Error: monitoring failed to fork.\n");
	else if (code == EPIPE)
		fprintf(stderr, "Error: monitoring failed to open pipe.\n");
	exit(EXIT_FAILURE);
}

int	check_file_format(char **line, char *interval, int method)
{
	int num_col;

	num_col = 0;
	while (line[num_col])
		num_col++;
	if (num_col != method)
		return (INVINPUT);
	if (check_interval(interval) == 0){
		fprintf(stderr, "Interval '%s' invalid.\n", 
			(char *)ft_memrpl(interval, '\n', 0, ft_strlen(interval)));
		return (INVINPUT);
	}
	return (0);
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