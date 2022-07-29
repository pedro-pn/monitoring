/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:58:45 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/28 23:11:29 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	error_handle(int code)
{
	if (code == FILEOP)
		fprintf(stderr, "Failed to open 'monitoring.db'.\n");
	else if (code == INVINPUT)
		fprintf(stderr, "Invalid monitoring.db format!\n");
	else if (code == OUTFAIL)
		fprintf(stderr, "Can't create or modify 'monitoring.log'\n!");
	else if (code == NARG)
		fprintf(stderr, "Please insert 'monitoring.db'!\n");
	exit(EXIT_FAILURE);
}