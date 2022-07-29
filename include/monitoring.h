/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:25:57 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/29 16:05:37 by ppaulo-d         ###   ########.fr       */
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
# define NARG 4
# define INVARG 5
# define MONARG 6
# define INVPROTO 7
# define EINTERVAL 8

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

void	read_file(t_list **data, char *file_name);
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

#endif
