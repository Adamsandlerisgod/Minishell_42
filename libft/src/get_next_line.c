/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:33:32 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/07 17:19:35 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*read_file_helper(char *res, char *buffer, int b_r)
{
	if (b_r > 0)
	{
		if (ft_strchr(buffer, '\n'))
		{
			res = ft_free_join(res, buffer);
			buffer = NULL;
			return (res);
		}
		else
		{
			res = ft_free_join(res, buffer);
			buffer = NULL;
			return (res);
		}
	}
	else if (buffer && buffer[0] != '\n' && buffer[b_r] != '\n')
	{
		free(buffer);
		return (res);
	}
	return (res);
}

char	*read_file(int fd, char *res)
{
	int		b_r;
	char	*buffer;

	if (!res || res[0] == '\0')
	{
		res = specific_calloc(1, 1);
	}
	b_r = 1;
	while (b_r > 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		b_r = read(fd, buffer, BUFFER_SIZE);
		buffer[b_r] = 0;
		if (b_r < 0)
		{
			free(buffer);
			free(res);
			return (NULL);
		}
		res = read_file_helper(res, buffer, b_r);
		if (ft_strchr(res, '\n'))
			return (res);
	}
	return (res);
}

char	*ft_line(char *buffer)
{
	char	*res;
	int		i;
	int		len;

	if (!buffer)
		return (NULL);
	len = ft_strlen_gnl(buffer, '\n');
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = 0;
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		res[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		res[i] = '\n';
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*next_line(char *buffer)
{
	int		i;
	char	*line;
	int		j;

	i = ft_strlen_gnl(buffer, '\n');
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	line = malloc((ft_strlen_gnl(buffer, '\0') - i + 2) * sizeof(char));
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = 0;
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_line(buffer);
	buffer = next_line(buffer);
	return (line);
}
