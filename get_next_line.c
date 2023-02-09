/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 07:21:28 by gabriela          #+#    #+#             */
/*   Updated: 2023/02/07 13:49:04 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_rest(char **rest)
{
	char	*line;
	char	*nl_pos;
	char	*rest_update;

	if (*rest != NULL)
	{
		if (ft_strchr(*rest, '\n'))
		{
			nl_pos = ft_strchr(*rest, '\n');
			rest_update = ft_strdup(nl_pos + 1);
			*(nl_pos + 1) = '\0';
			line = ft_strdup(*rest);
			free(*rest);
			*rest = rest_update;
		}
		else
		{
			line = *rest;
			*rest = NULL;
		}
	}
	else
		line = ft_strdup("");
	return (line);
}

char	*ft_read_line(int fd, char *line, char **rest, int reading)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line_update;
	char	*nl_pos;

	while (reading > 0 && !ft_strchr(line, '\n') && !(*rest))
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading == 0 && *line == '\0')
		{
			free(line);
			return (NULL);
		}
		buffer[reading] = '\0';
		if (ft_strchr(buffer, '\n'))
		{
			nl_pos = ft_strchr(buffer, '\n');
			*rest = ft_strdup(nl_pos + 1);
			*(nl_pos + 1) = '\0';
		}
		line_update = line;
		line = ft_strjoin(line, buffer);
		free(line_update);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	int			reading;
	char		buffer[1];

	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFFER_SIZE < 0)
		return (NULL);
	reading = 1;
	line = ft_get_rest(&rest);
	line = ft_read_line(fd, line, &rest, reading);
	return (line);
}
