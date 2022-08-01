/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:25:57 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 13:28:17 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>

# define FILEOP 2
# define INVINPUT 3
# define OUTFAIL 4
# define INVARG 5
# define MANYARGS 6
# define INVPROTO 7
# define EINTERVAL 8
# define EFORK	9
# define EPIPE 10
# define HTTP 6
# define PING 4
# define DNS 5
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
int		start_ping(t_data data, int output);
int		start_http(t_data data, int output);
int		start_dns(t_data data, int output);
void	check_args(int argc, char *argv[]);
void	print_menu(int output);
void	monitoring_init(t_list **data, int argc, char *argv[], int *output);
int		monitoring_start(t_list *data, int output_fd);
int		write_ping(t_data data, int pipe, int fd_log);
int		write_http(t_data data, int pipe, int fd_log);
int		write_dns(t_data data, int pipe, int fd_log);
void	check_file_format(char **line, t_list **data, char *interval, int method);

#endif
