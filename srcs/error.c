/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:58:45 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/27 22:03:27 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	error_handle(int code)
{
	if (code == FILEOP)
		fprintf(stderr, "Failed to open file!\n");
	else if (code == INVINPUT)
		fprintf(stderr, "Invalid monitoring.db format!\n");
	exit(EXIT_FAILURE);
}