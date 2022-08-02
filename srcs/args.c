/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 10:26:51 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/02 11:14:15 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

static void	recover_log(void);

void	check_args(int argc, char *argv[])
{
	if (argc > 2)
		error_handle(MANYARGS);
	else if (argc == 2)
	{
		if (!strcmp(argv[1],  "--simplify"))
			recover_log();
		else
			error_handle(INVARG);
	}
}

static void	recover_log(void)
{
	int		log;
	char	*line;

	log = open(LGFILE, O_RDONLY);
	if (log < 0)
	{
		fprintf(stderr, "Fail to read 'monitoring.log'\n");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(log);
	while (line)
	{
		if (!ft_strncmp(line, "# ", 2))
			ft_printf("%s", line);
		free(line);
		line = get_next_line(log);
	}
	close(log);
	exit(EXIT_SUCCESS);
}
