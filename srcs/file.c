/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:34:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/01 13:27:52 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

static void	fill_data(t_list **data, char **line);
static void	fill_http(t_list **data, char **line);
static void	fill_ping(t_list **data, char **line);
static void	fill_dns(t_list **data, char **line);

void	read_file(t_list **data)
{
	int		fd;
	char	*line;
	char	**splt_line;

	fd = open(DBFILE, O_RDONLY);
	if (fd < 0)
		error_handle(FILEOP, NULL);
	line = get_next_line(fd);
	while (line)
	{
		splt_line = ft_split(line, '\t');
		free(line);
		fill_data(data, splt_line);
		free(splt_line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	fill_data(t_list **data, char **line)
{
	if (!strcmp(line[1], "HTTP"))
		fill_http(data, line);
	else if (!strcmp(line[1], "PING"))
		fill_ping(data, line);
	else if (!strcmp(line[1], "DNS"))
		fill_dns(data, line);
	else{
		ft_lstclear(data, clean_data);
		error_handle(INVPROTO, line[1]);
		clean_array((void **)line);
		exit(EXIT_FAILURE);
	}
}

static void	fill_http(t_list **data, char **line)
{
	t_data	*content;

	check_file_format(line, data, line[5], HTTP);
	content = malloc(sizeof(*content));
	content->name = line[0];
	content->protocol = line[1];
	content->address = line[2];
	content->http_method = line[3];
	content->http_code = ft_atoi(line[4]);
	content->interval = ft_atoi(line[5]);
	content->dns_server = NULL;
	free(line[4]);
	free(line[5]);
	ft_lstadd_back(data, ft_lstnew(content));
}

static void	fill_ping(t_list **data, char **line)
{
	t_data	*content;

	check_file_format(line, data, line[3], PING);
	content = malloc(sizeof(*content));
	content->name = line[0];
	content->protocol = line[1];
	content->address = line[2];
	content->http_method = 0;
	content->http_code = 0;
	content->interval = ft_atoi(line[3]);
	content->dns_server = NULL;
	free(line[3]);
	ft_lstadd_back(data, ft_lstnew(content));
}

static void	fill_dns(t_list **data, char **line)
{
	t_data	*content;

	check_file_format(line, data, line[3], DNS);
	content = malloc(sizeof(*content));
	content->name = line[0];
	content->protocol = line[1];
	content->address = line[2];
	content->http_method = 0;
	content->http_code = 0;
	content->interval = ft_atoi(line[3]);
	content->dns_server = ft_strtrim(line[4], "\n \t");
	free(line[3]);
	free(line[4]);
	ft_lstadd_back(data, ft_lstnew(content));
}

void	clean_array(void **array)
{
	int	index;

	index = 0;
	while(array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

void	clean_data(void *content)
{
	t_data *cont;

	cont = (t_data *)content;
	if (cont->address)
		free(cont->address);
	if (cont->dns_server)
		free(cont->dns_server);
	if (cont->http_method)
		free(cont->http_method);
	if (cont->name)
		free(cont->name);
	if (cont->protocol)
		free(cont->protocol);
	free(content);
}
