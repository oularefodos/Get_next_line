/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:34:19 by foulare           #+#    #+#             */
/*   Updated: 2021/11/16 21:55:07 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_checkline(char *result)
{
	int	i;

	i = 0;
	while (result[i] != '\0' && result[i] != '\n')
		i++;
	return (i);
}

int	ft_error(ssize_t ret, char *buf, char *result)
{
	if (ret < 0)
	{
		free(buf);
		if (result != NULL)
			free(result);
		return (1);
	}
	else if (ret == 0 && result == NULL)
	{
		free(buf);
		return (1);
	}
	else if (result[0] == '\0')
	{
		free(result);
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}

char	*ft_remp(char *result, char *buf, int fd)
{
	char	*temp;
	ssize_t	ret;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = 0;
		if (result == 0)
			result = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(result, buf);
			free(result);
			result = temp;
		}
		if (ft_strchr(result, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	if (ft_error(ret, buf, result))
		return (0);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*result[65535];
	char		*temp;
	char		*line;
	char		*buf;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = NULL;
	result[fd] = ft_remp(result[fd], buf, fd);
	if (!result[fd])
		return (0);
	if (result[fd][ft_checkline(result[fd])] == '\n')
	{
		line = ft_substr(result[fd], 0, ft_checkline(result[fd]) + 1);
		temp = ft_strdup(&result[fd][ft_checkline(result[fd]) + 1]);
		free(result[fd]);
		result[fd] = temp;
	}
	else
	{
		line = ft_strdup(result[fd]);
		free(result[fd]);
		result[fd] = NULL;
	}
	return (line);
}
