/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:58:45 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 16:49:51 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	error_handle(int code, char *name)
{
	if (code == FILEOP)
		fprintf(stderr, "Failed to open 'monitoring.db'.\n");
	else if (code == INVINPUT)
		fprintf(stderr, "Invalid format in 'monitoring.db' file.\n");
	else if (code == OUTFAIL)
		fprintf(stderr, "Can't create or modify 'monitoring.log'.\n");
	else if (code == NARG)
		fprintf(stderr, "Please insert 'monitoring.db' or use '--simplify' to visualize log.\n");
	else if (code == INVARG)
		fprintf(stderr, "Arguments invalid.\n");
	else if (code == MONARG)
		fprintf(stderr, "Only 'monitoring.db' file is valid.\n");
	else if (code == INVPROTO){
		fprintf(stderr, "'%s' protocol invalid.\n", name);
		return ;
	}
	else if (code == EINTERVAL){
		fprintf(stderr, "Interval '%s' invalid.\n", (char *)ft_memrpl(name, '\n', 0, ft_strlen(name)));
		return ;
	}
	exit(EXIT_FAILURE);
}