/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 10:26:51 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 16:18:33 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

static void	recover_log(void);

void	check_args(int argc, char *argv[])
{
	if (argc < 2)
		error_handle(NARG, NULL);
	else if (argc > 3)
		error_handle(INVARG, NULL);
	else if (argc == 2){
		if (!ft_strncmp(argv[1],  "--simplify", ft_strlen(argv[1]))
			&& ft_strlen(argv[1]) == 10){
			recover_log();
			exit(EXIT_SUCCESS);
		}
		else if (ft_strncmp(argv[1],  "monitoring.db", ft_strlen(argv[1]))
				|| ft_strlen(argv[1]) != 13)
			error_handle(NARG, NULL);
	}
	else if (argc == 3){
		if ((!ft_strncmp(argv[1],  "--simplify", ft_strlen(argv[1])) && ft_strlen(argv[1]) == 10)
			|| (!ft_strncmp(argv[2],  "--simplify", ft_strlen(argv[2])) && ft_strlen(argv[2]) == 10))
			recover_log();
		else
			error_handle(INVARG, NULL);
		if ((ft_strncmp(argv[1],  "monitoring.db", ft_strlen(argv[1])) || ft_strlen(argv[1]) != 13)
			&& (ft_strncmp(argv[2],  "monitoring.db", ft_strlen(argv[2])) || ft_strlen(argv[2]) != 13))
			error_handle(MONARG, NULL);
	}
}

static void	recover_log(void)
{
	int		log;
	char	*line;
	
	log = open("monitoring.log", O_RDONLY);
	if (log < 0){
		fprintf(stderr, "Fail to read 'monitoring.log'\n");
		return ;
	}
	line = get_next_line(log);
	while (line){
		if (!ft_strncmp(line, "# ", 2))
			ft_printf("%s", line);
		free(line);
		line = get_next_line(log);
	}
	close(log);
}