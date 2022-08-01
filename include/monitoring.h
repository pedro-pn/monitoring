/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:25:57 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 16:57:21 by ppaulo-d         ###   ########.fr       */
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
# define EFORK	7
# define EPIPE 8
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

// monitoring.db file handle functions

/* Read monitoring.db and fill a linked list with each line */
void	read_file(t_list **data);
/* Clean a two dimentional array*/
void	clean_array(void **array);
/* Clean the content of linked list*/
void	clean_data(void *content);
/* Check if the configuration in 'monitoring.db' file is properly formatted*/
int	check_file_format(char **line, char *interval, int method);


// monitoring executing functions

/* Initialize monitoring checking *argv[] and setting up the linked list*/
void	monitoring_init(t_list **data, int argc, char *argv[], int *log_fd);
/* Execute each 'monitoring.db' entry properly */
int		monitoring_start(t_list *data, int log_fd);
/* Execute PING protocol*/
int		start_ping(t_data data, int log_fd);
/* Execute HTTP protocol */
int		start_http(t_data data, int log_fd);
/* Execute DNS protocol */
int		start_dns(t_data data, int log_fd);


// formatting log_fd functions

/* Write the 'monitoring.db' configuration to 'monitoring.log' file*/
void	print_menu(int log_fd);
/* Format the output of PING protocol and write to STDOUT and 'monitoring.log' file*/
void	format_out_ping(char *line, t_data content, int log_fd);
/* Format the output of HTTP protocol and write to STDOUT and 'monitoring.log' file*/
void	format_out_http(char *line, t_data content, int log_fd);
/* Format the output of DNS protocol and write to STDOUT and 'monitoring.log' file*/
void	format_out_dns(char *line, t_data content, int log_fd);
/* Read the output of PING protocol*/
int		write_ping(t_data data, int pipe, int log_fd);
/* Read the output of HTTP protocol*/
int		write_http(t_data data, int pipe, int log_fd);
/* Read the output of DNS protocol*/
int		write_dns(t_data data, int pipe, int log_fd);


// error handling functions

/* Exit program and print error to stderr */
void	error_handle(int code);
/* Check args received from program call */
void	check_args(int argc, char *argv[]);

#endif
