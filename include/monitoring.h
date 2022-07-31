/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:25:57 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/30 23:15:38 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>

# define FILEOP 1
# define INVINPUT 2
# define OUTFAIL 3
# define INVARG 4
# define MANYARGS 5
# define INVPROTO 6
# define EINTERVAL 7
# define DBFILE "monitoring.db"
# define LGFILE "monitoring.log"

typedef struct s_data
{
	char	*name;
	char	*protocol;
	char	*address;
	char	*http_method;
	int		http_code;
	int		interval;
	char	*dns_server;
}			t_data;

void	read_file(t_list **data);
void	error_handle(int code, char *name);
void	clean_array(void **array);
void	clean_data(void *content);
void	format_out_ping(char *line, t_data content, int output);
void	format_out_http(char *line, t_data content, int output);
void	format_out_dns(char *line, t_data content, int output);
void	start_ping(t_data data, int output);
void	start_http(t_data data, int output);
void	start_dns(t_data data, int output);
void	check_args(int argc, char *argv[]);
void	print_menu(int output);
void	monitoring_init(t_list **data, int argc, char *argv[], int *output);
void	monitoring_start(t_list *data, int output_fd);

#endif
