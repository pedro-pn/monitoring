/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:25:57 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/28 20:10:08 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

# define FILEOP 1
# define INVINPUT 2

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

void	data_init(t_data *data);
void	read_file(t_list **data, char *file_name);
void	fill_data(t_list **data, char **line);
void	fill_http(t_list **data, char **line);
void	fill_ping(t_list **data, char **line);
void	fill_dns(t_list **data, char **line);
void	error_handle(int code);
void	clean_array(void **array);
void	clean_data(void *content);
void	format_out_ping(char *line, t_data content, int output);
void	format_out_http(char *line, t_data content, int output);
void	format_out_dns(char *line, t_data content, int output);
// typedef struct s_http
// {
// 	char	*name;
// 	char	*protocol;
// 	char	*address;
// 	char	*http_method;
// 	char	*http_code;
// 	char	*interval;
// }				t_http;

// typedef struct s_ping
// {
// 	char	*name;
// };



#endif